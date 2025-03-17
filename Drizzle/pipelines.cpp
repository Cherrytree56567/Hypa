#include "Vulkan.h"

namespace Drizzle {
    bool Vulkan::load_shader_module(const char* filePath, VkDevice device, VkShaderModule* outShaderModule) {
        /*
        * Open the file.
        * With cursor at the end
        */
        std::ifstream file(filePath, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            return false;
        }

        /*
        * Find what the size of the file is by looking up the location of the cursor
        * because the cursor is at the end, it gives the size directly in bytes
        */
        size_t fileSize = (size_t)file.tellg();

        /*
        * Spir-V expects the buffer to be on uint32, so make sure to reserve a int
        * vector big enough for the entire file
        */
        std::vector<uint32_t> buffer(fileSize / sizeof(uint32_t));

        /*
        * Put file cursor at beginning
        */
        file.seekg(0);

        /*
        * Load the entire file into the buffer
        */
        file.read((char*)buffer.data(), fileSize);

        /*
        * Now that the file is loaded into the buffer, we can close it
        */
        file.close();

        /*
        * Create a new shader module, using the buffer we loaded
        */
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.pNext = nullptr;

        /*
        * codeSize has to be in bytes, so multply the ints in the buffer by size of
        * int to know the real size of the buffer
        */
        createInfo.codeSize = buffer.size() * sizeof(uint32_t);
        createInfo.pCode = buffer.data();

        /*
        * Check that the creation goes well.
        */
        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            return false;
        }
        *outShaderModule = shaderModule;
        return true;
    }
}