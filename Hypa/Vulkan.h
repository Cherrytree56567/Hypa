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

#include <vulkan/vulkan.h>
#include <vulkan/vk_enum_string_helper.h>
#include <vk_mem_alloc.h>
#include <VkBootstrap/VkBootstrap.h>

#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>
#define VK_CHECK(x)                                                     \
    do {                                                                \
        VkResult err = x;                                               \
        if (err) {                                                      \
             fmt::print("Detected Vulkan error: {}", string_VkResult(err)); \
            abort();                                                    \
        }                                                               \
    } while (0)

namespace Hypa {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

	class Vulkan : public RenderingAPI {
	public:
		HYPA_API Vulkan(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events);

		HYPA_API void OnAttach() override;
		HYPA_API void OnDetach() override;
		HYPA_API void Render() override;

		HYPA_API const std::string& GetName() const override;
        HYPA_API void resize_framebuffer(bool tof);
        HYPA_API void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) override;
        HYPA_API std::tuple<VkShaderModule, VkShaderModule, UniformBufferObject> GetShader(std::string name);
        HYPA_API void RemoveShader(std::string name) override;
        HYPA_API void ChangeShader(std::string name) override;
        HYPA_API std::string GetCurrentShaderName() override;

        HYPA_API void DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) override;

        HYPA_API void AddUniform(std::string name, UniformBufferObject& ubo) override;

	private:
        
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        int rateDeviceSuitability(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        std::pair<VkShaderModule, VkShaderModule> Create_VulkanShader(const char* vertexShaderSource, const char* fragmentShaderSource);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void updateUniformBuffer(uint32_t currentImage);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void OtherHalfUpdateUniform();
        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            return attributeDescriptions;
        }

        void createInstance();
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createSwapChain();
        void createImageViews();
        VkPipeline createGraphicsPipeline(VkViewport viewport);
        void createRenderPass();
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffers();
        void createSyncObjects();
        void drawFrame();
        void cleanupSwapChain();
        void recreateSwapChain();
        void createVertexBuffer(std::vector<Vertex> vertices);
        void createIndexBuffer(std::vector<uint16_t> indices);
        void createDescriptorSetLayout();
        void createUniformBuffers();
        void createDescriptorPool();
        void createDescriptorSets();

		Flags flags;
		std::string name;
        std::string CurrentShaderName = "Default";
        Logging log;
        bool ShaderChanged = false;
        std::shared_ptr<Window> pWindow;
        std::shared_ptr<EventSystem> pEvents;
        std::map<std::string, std::tuple<VkShaderModule, VkShaderModule, UniformBufferObject>> Shaders;

        size_t Uniformoffset = 0;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkDevice device;
        VkQueue graphicsQueue;
        std::vector<std::vector<VkPushConstantRange>> pushConstantRanges;
        std::vector<int> pushConstantRangesOffset;
        std::vector<VkBuffer> OLDvertexBuffer;
        std::vector<VkDeviceMemory> OLDvertexBufferMemory;
        std::vector<VkBuffer> OLDindexBuffer;
        std::vector<VkDeviceMemory> OLDindexBufferMemory;
        std::vector<VkBuffer> vertexBuffer;
        std::vector<VkDeviceMemory> vertexBufferMemory;
        std::vector<VkBuffer> indexBuffer;
        std::vector<VkDeviceMemory> indexBufferMemory;
        std::vector<int> IndicesSize;

        VkViewport viewport{};

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        std::vector<void*> uniformBuffersMapped;
        VkSurfaceKHR surface;
        VkQueue presentQueue;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        VkRenderPass renderPass;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline DefaultgraphicsPipeline;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        const int MAX_FRAMES_IN_FLIGHT = 2;
        uint32_t currentFrame = 0;
        bool framebufferResized = false;
        const uint32_t WIDTH = 800;
        const uint32_t HEIGHT = 600;
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else
        const bool enableValidationLayers = true;
#endif
	};
}