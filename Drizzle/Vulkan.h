#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include "base.h"
#include "Window.h"
#include "RenderingAPI.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <span>
#include <fstream>
#include <algorithm>
#include <array>
#include <functional>
#include <deque>
#include <set>
#include <variant>

#include <vulkan/vulkan.h>
#include <vulkan/vk_enum_string_helper.h>
#include <vk_mem_alloc.h>
#include <VkBootstrap/VkBootstrap.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_vulkan.h>

#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>
#include "RenderingAPI.h"
#define VK_CHECK(x)                                                     \
    do {                                                                \
        VkResult err = x;                                               \
        if (err) {                                                      \
            std::cout << "Detected Vulkan error: " << string_VkResult(err); \
            abort();                                                    \
        }                                                               \
    } while (0)

namespace Drizzle {
    struct DescriptorLayoutBuilder {

        std::vector<VkDescriptorSetLayoutBinding> bindings;

        void add_binding(uint32_t binding, VkDescriptorType type);
        void clear();
        VkDescriptorSetLayout build(VkDevice device, VkShaderStageFlags shaderStages, void* pNext = nullptr, VkDescriptorSetLayoutCreateFlags flags = 0);
    };

    struct DescriptorAllocator {

        struct PoolSizeRatio {
            VkDescriptorType type;
            float ratio;
        };

        VkDescriptorPool pool;

        void init_pool(VkDevice device, uint32_t maxSets, std::span<PoolSizeRatio> poolRatios);
        void clear_descriptors(VkDevice device);
        void destroy_pool(VkDevice device);

        VkDescriptorSet allocate(VkDevice device, VkDescriptorSetLayout layout);
    };

    struct DeletionQueue {
        std::deque<std::function<void()>> deletors;

        void push_function(std::function<void()>&& function) {
            deletors.push_back(function);
        }

        void flush() {
            for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
                (*it)();
            }

            deletors.clear();
        }
    };

    struct AllocatedImage {
        VkImage image;
        VkImageView imageView;
        VmaAllocation allocation;
        VkExtent3D imageExtent;
        VkFormat imageFormat;
    };

    struct FrameData {
        VkSemaphore _swapchainSemaphore, _renderSemaphore;
        VkFence _renderFence;
        VkCommandPool _commandPool;
        VkCommandBuffer _mainCommandBuffer;
        DeletionQueue _deletionQueue;
    };

    struct ComputeEffect {
        const char* name;

        VkPipeline pipeline;
        VkPipelineLayout layout;

        PushConstants data;
    };

	class Vulkan : public RenderingAPI {
	public:
		Drizzle_API Vulkan(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events);

		Drizzle_API void OnAttach() override;
		Drizzle_API void OnDetach() override;
		Drizzle_API void Render() override;

		Drizzle_API const std::string& GetName() const override;
        Drizzle_API void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) override;
        Drizzle_API void RemoveShader(std::string name) override;
        Drizzle_API void ChangeShader(std::string name) override;
        Drizzle_API std::string GetCurrentShaderName() override;

        Drizzle_API void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) override;

        Drizzle_API PushConstants& GetPushConstants() override;

	private:
        void init_vulkan();
        void init_swapchain();
        void init_commands();
        void init_sync_structures();
        void init_descriptors();
        void init_pipelines();
        void init_background_pipelines();
        void init_imgui();
        void draw_imgui(VkCommandBuffer cmd, VkImageView targetImageView);
        void create_swapchain(uint32_t width, uint32_t height);
        void destroy_swapchain();
        void draw_background(VkCommandBuffer cmd);

        FrameData& get_current_frame();
        VkCommandPoolCreateInfo command_pool_create_info(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags);
        VkCommandBufferAllocateInfo command_buffer_allocate_info(VkCommandPool pool, uint32_t count);
        VkFenceCreateInfo fence_create_info(VkFenceCreateFlags flags);
        VkSemaphoreCreateInfo semaphore_create_info(VkSemaphoreCreateFlags flags);
        VkCommandBufferBeginInfo command_buffer_begin_info(VkCommandBufferUsageFlags flags);
        VkSemaphoreSubmitInfo semaphore_submit_info(VkPipelineStageFlags2 stageMask, VkSemaphore semaphore);
        VkCommandBufferSubmitInfo command_buffer_submit_info(VkCommandBuffer cmd);
        VkSubmitInfo2 submit_info(VkCommandBufferSubmitInfo* cmd, VkSemaphoreSubmitInfo* signalSemaphoreInfo, VkSemaphoreSubmitInfo* waitSemaphoreInfo);
        VkImageCreateInfo image_create_info(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent);
        VkImageViewCreateInfo imageview_create_info(VkFormat format, VkImage image, VkImageAspectFlags aspectFlags);

        void transition_image(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout);
        VkImageSubresourceRange image_subresource_range(VkImageAspectFlags aspectMask);
        void copy_image_to_image(VkCommandBuffer cmd, VkImage source, VkImage destination, VkExtent2D srcSize, VkExtent2D dstSize);
        void immediate_submit(std::function<void(VkCommandBuffer cmd)>&& function);
        VkRenderingAttachmentInfo attachment_info(VkImageView view, VkClearValue* clear, VkImageLayout layout);
        VkRenderingInfo rendering_info(VkExtent2D renderExtent, VkRenderingAttachmentInfo* colorAttachment, VkRenderingAttachmentInfo* depthAttachment);

        bool load_shader_module(const char* filePath, VkDevice device, VkShaderModule* outShaderModule);

		Flags flags;
		std::string name;
        std::string CurrentShaderName = "Default";
        Logging log;
        bool ShaderChanged = false;
        std::shared_ptr<Window> pWindow;
        std::shared_ptr<EventSystem> pEvents;
		PushConstants pc;

        VkInstance _instance;
        VkDebugUtilsMessengerEXT _debug_messenger;
        VkPhysicalDevice _chosenGPU;
        VkDevice _device;
        VkSurfaceKHR _surface;
        VkSwapchainKHR _swapchain;
        VkFormat _swapchainImageFormat;
        VkQueue _graphicsQueue;
        VmaAllocator _allocator;
        VkDescriptorSet _drawImageDescriptors;
        VkDescriptorSetLayout _drawImageDescriptorLayout;
        VkPipeline _gradientPipeline;
        VkPipelineLayout _gradientPipelineLayout;
        /*
        * ImGUI
        */
        VkFence _immFence;
        VkCommandBuffer _immCommandBuffer;
        VkCommandPool _immCommandPool;

        std::vector<VkImage> _swapchainImages;
        std::vector<VkImageView> _swapchainImageViews;
        VkExtent2D _swapchainExtent;
        static const unsigned int FRAME_OVERLAP = 2;
        FrameData _frames[FRAME_OVERLAP];
        int _frameNumber{ 0 };
        uint32_t _graphicsQueueFamily;
        DeletionQueue _mainDeletionQueue;
        AllocatedImage _drawImage;
        VkExtent2D _drawExtent;
        DescriptorAllocator globalDescriptorAllocator;
        std::vector<ComputeEffect> backgroundEffects;
        int currentBackgroundEffect{ 0 };

#ifdef NDEBUG
        const bool bUseValidationLayers = false;
#else
        const bool bUseValidationLayers = true;
#endif
	};
}