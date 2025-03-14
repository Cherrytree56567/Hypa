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

namespace Drizzle {


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

        Drizzle_API void AddUniform(std::string name, UniformBufferObject& ubo) override;

	private:

        void init_vulkan();
        void init_swapchain();
        void init_commands();
        void init_sync_structures();

		Flags flags;
		std::string name;
        std::string CurrentShaderName = "Default";
        Logging log;
        bool ShaderChanged = false;
        std::shared_ptr<Window> pWindow;
        std::shared_ptr<EventSystem> pEvents;

        VkInstance _instance;
        VkDebugUtilsMessengerEXT _debug_messenger;
        VkPhysicalDevice _chosenGPU;
        VkDevice _device;
        VkSurfaceKHR _surface;
	};
}