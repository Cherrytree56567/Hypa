#include "Vulkan.h"

namespace Drizzle {
    void DescriptorLayoutBuilder::add_binding(uint32_t binding, VkDescriptorType type) {
        VkDescriptorSetLayoutBinding newbind{};
        newbind.binding = binding;
        newbind.descriptorCount = 1;
        newbind.descriptorType = type;

        bindings.push_back(newbind);
    }

    void DescriptorLayoutBuilder::clear() {
        bindings.clear();
    }

    VkDescriptorSetLayout DescriptorLayoutBuilder::build(VkDevice device, VkShaderStageFlags shaderStages, void* pNext, VkDescriptorSetLayoutCreateFlags flags) {
        for (auto& b : bindings) {
            b.stageFlags |= shaderStages;
        }

        VkDescriptorSetLayoutCreateInfo info = { .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
        info.pNext = pNext;

        info.pBindings = bindings.data();
        info.bindingCount = (uint32_t)bindings.size();
        info.flags = flags;

        VkDescriptorSetLayout set;
        VK_CHECK(vkCreateDescriptorSetLayout(device, &info, nullptr, &set));

        return set;
    }

    void DescriptorAllocator::init_pool(VkDevice device, uint32_t maxSets, std::span<PoolSizeRatio> poolRatios) {
        std::vector<VkDescriptorPoolSize> poolSizes;
        for (PoolSizeRatio ratio : poolRatios) {
            poolSizes.push_back(VkDescriptorPoolSize{
                .type = ratio.type,
                .descriptorCount = uint32_t(ratio.ratio * maxSets)
                });
        }

        VkDescriptorPoolCreateInfo pool_info = { .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
        pool_info.flags = 0;
        pool_info.maxSets = maxSets;
        pool_info.poolSizeCount = (uint32_t)poolSizes.size();
        pool_info.pPoolSizes = poolSizes.data();

        vkCreateDescriptorPool(device, &pool_info, nullptr, &pool);
    }

    void DescriptorAllocator::clear_descriptors(VkDevice device) {
        vkResetDescriptorPool(device, pool, 0);
    }

    void DescriptorAllocator::destroy_pool(VkDevice device) {
        vkDestroyDescriptorPool(device, pool, nullptr);
    }

    VkDescriptorSet DescriptorAllocator::allocate(VkDevice device, VkDescriptorSetLayout layout)  {
        VkDescriptorSetAllocateInfo allocInfo = { .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
        allocInfo.pNext = nullptr;
        allocInfo.descriptorPool = pool;
        allocInfo.descriptorSetCount = 1;
        allocInfo.pSetLayouts = &layout;

        VkDescriptorSet ds;
        VK_CHECK(vkAllocateDescriptorSets(device, &allocInfo, &ds));

        return ds;
    }


    VkDescriptorPool DescriptorAllocatorGrowable::get_pool(VkDevice device) {
        VkDescriptorPool newPool;
        if (readyPools.size() != 0) {
            newPool = readyPools.back();
            readyPools.pop_back();
        } else {
            newPool = create_pool(device, setsPerPool, ratios);

            setsPerPool = setsPerPool * 1.5;
            if (setsPerPool > 4092) {
                setsPerPool = 4092;
            }
        }

        return newPool;
    }

    VkDescriptorPool DescriptorAllocatorGrowable::create_pool(VkDevice device, uint32_t setCount, std::span<PoolSizeRatio> poolRatios) {
        std::vector<VkDescriptorPoolSize> poolSizes;
        for (PoolSizeRatio ratio : poolRatios) {
            poolSizes.push_back(VkDescriptorPoolSize{
                .type = ratio.type,
                .descriptorCount = uint32_t(ratio.ratio * setCount)
            });
        }

        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.flags = 0;
        pool_info.maxSets = setCount;
        pool_info.poolSizeCount = (uint32_t)poolSizes.size();
        pool_info.pPoolSizes = poolSizes.data();

        VkDescriptorPool newPool;
        vkCreateDescriptorPool(device, &pool_info, nullptr, &newPool);
        return newPool;
    }

    void DescriptorAllocatorGrowable::init(VkDevice device, uint32_t maxSets, std::span<PoolSizeRatio> poolRatios) {
        ratios.clear();

        for (auto r : poolRatios) {
            ratios.push_back(r);
        }

        VkDescriptorPool newPool = create_pool(device, maxSets, poolRatios);

        setsPerPool = maxSets * 1.5;

        readyPools.push_back(newPool);
    }

    void DescriptorAllocatorGrowable::clear_pools(VkDevice device) {
        for (auto p : readyPools) {
            vkResetDescriptorPool(device, p, 0);
        }

        for (auto p : fullPools) {
            vkResetDescriptorPool(device, p, 0);
            readyPools.push_back(p);
        }

        fullPools.clear();
    }

    void DescriptorAllocatorGrowable::destroy_pools(VkDevice device) {
        for (auto p : readyPools) {
            vkDestroyDescriptorPool(device, p, nullptr);
        }

        readyPools.clear();

        for (auto p : fullPools) {
            vkDestroyDescriptorPool(device, p, nullptr);
        }

        fullPools.clear();
    }

    VkDescriptorSet DescriptorAllocatorGrowable::allocate(VkDevice device, VkDescriptorSetLayout layout, void* pNext) {
        VkDescriptorPool poolToUse = get_pool(device);

        VkDescriptorSetAllocateInfo allocInfo = {};
        allocInfo.pNext = pNext;
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = poolToUse;
        allocInfo.descriptorSetCount = 1;
        allocInfo.pSetLayouts = &layout;

        VkDescriptorSet ds;
        VkResult result = vkAllocateDescriptorSets(device, &allocInfo, &ds);

        if (result == VK_ERROR_OUT_OF_POOL_MEMORY || result == VK_ERROR_FRAGMENTED_POOL) {

            fullPools.push_back(poolToUse);

            poolToUse = get_pool(device);
            allocInfo.descriptorPool = poolToUse;

            VK_CHECK(vkAllocateDescriptorSets(device, &allocInfo, &ds));
        }

        readyPools.push_back(poolToUse);
        return ds;
    }

    void DescriptorWriter::write_buffer(int binding, VkBuffer buffer, size_t size, size_t offset, VkDescriptorType type) {
        VkDescriptorBufferInfo& info = bufferInfos.emplace_back(VkDescriptorBufferInfo{
            .buffer = buffer,
            .offset = offset,
            .range = size
        });

        VkWriteDescriptorSet write = { .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };

        write.dstBinding = binding;
        write.dstSet = VK_NULL_HANDLE;
        write.descriptorCount = 1;
        write.descriptorType = type;
        write.pBufferInfo = &info;

        writes.push_back(write);
    }

    void DescriptorWriter::write_image(int binding, VkImageView image, VkSampler sampler, VkImageLayout layout, VkDescriptorType type) {
        VkDescriptorImageInfo& info = imageInfos.emplace_back(VkDescriptorImageInfo{
            .sampler = sampler,
            .imageView = image,
            .imageLayout = layout
            });

        VkWriteDescriptorSet write = { .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };

        write.dstBinding = binding;
        write.dstSet = VK_NULL_HANDLE;
        write.descriptorCount = 1;
        write.descriptorType = type;
        write.pImageInfo = &info;

        writes.push_back(write);
    }

    void DescriptorWriter::clear() {
        imageInfos.clear();
        writes.clear();
        bufferInfos.clear();
    }

    void DescriptorWriter::update_set(VkDevice device, VkDescriptorSet set) {
        for (VkWriteDescriptorSet& write : writes) {
            write.dstSet = set;
        }

        vkUpdateDescriptorSets(device, (uint32_t)writes.size(), writes.data(), 0, nullptr);
    }

    AllocatedImage Vulkan::create_image(VkExtent3D size, VkFormat format, VkImageUsageFlags usage, bool mipmapped) {
        AllocatedImage newImage;
        newImage.imageFormat = format;
        newImage.imageExtent = size;

        VkImageCreateInfo img_info = image_create_info(format, usage, size);
        if (mipmapped) {
            img_info.mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(size.width, size.height)))) + 1;
        }

        /*
        * Always allocate images on dedicated GPU memory
        */
        VmaAllocationCreateInfo allocinfo = {};
        allocinfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
        allocinfo.requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        /*
        * Allocate and create the image
        */
        VK_CHECK(vmaCreateImage(_allocator, &img_info, &allocinfo, &newImage.image, &newImage.allocation, nullptr));

        /*
        * If the format is a depth format, we will need to have it use the correct
        * aspect flag
        */
        VkImageAspectFlags aspectFlag = VK_IMAGE_ASPECT_COLOR_BIT;
        if (format == VK_FORMAT_D32_SFLOAT) {
            aspectFlag = VK_IMAGE_ASPECT_DEPTH_BIT;
        }

        /*
        * Build a image - view for the image
        */
        VkImageViewCreateInfo view_info = imageview_create_info(format, newImage.image, aspectFlag);
        view_info.subresourceRange.levelCount = img_info.mipLevels;

        VK_CHECK(vkCreateImageView(_device, &view_info, nullptr, &newImage.imageView));

        return newImage;
    }

    AllocatedImage Vulkan::create_image(void* data, VkExtent3D size, VkFormat format, VkImageUsageFlags usage, bool mipmapped) {
        size_t data_size = size.depth * size.width * size.height * 4;
        AllocatedBuffer uploadbuffer = create_buffer(data_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU);

        memcpy(uploadbuffer.info.pMappedData, data, data_size);

        AllocatedImage new_image = create_image(size, format, usage | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, mipmapped);

        immediate_submit([&](VkCommandBuffer cmd) {
            transition_image(cmd, new_image.image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

            VkBufferImageCopy copyRegion = {};
            copyRegion.bufferOffset = 0;
            copyRegion.bufferRowLength = 0;
            copyRegion.bufferImageHeight = 0;

            copyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            copyRegion.imageSubresource.mipLevel = 0;
            copyRegion.imageSubresource.baseArrayLayer = 0;
            copyRegion.imageSubresource.layerCount = 1;
            copyRegion.imageExtent = size;

            /*
            * Copy the buffer into the image
            */
            vkCmdCopyBufferToImage(cmd, uploadbuffer.buffer, new_image.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);

            transition_image(cmd, new_image.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        });

        destroy_buffer(uploadbuffer);

        return new_image;
    }

    void Vulkan::destroy_image(const AllocatedImage& img) {
        vkDestroyImageView(_device, img.imageView, nullptr);
        vmaDestroyImage(_allocator, img.image, img.allocation);
    }
}