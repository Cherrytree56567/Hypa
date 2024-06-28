#include "Vulkan.h"

namespace Hypa {
	Vulkan::Vulkan(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events) {
		name = "Vulkan";
        pWindow = window;
        pEvents = Events;
	}

	const std::string& Vulkan::GetName() const {
		return name;
	}

    bool Vulkan::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    std::vector<const char*> Vulkan::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {

        Logging log;

        log.Warning(pCallbackData->pMessage, "[Hypa::Core::Vulkan] ");

        return VK_FALSE;
    }

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }

    void Vulkan::OnDetach() {
        cleanupSwapChain();

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroyBuffer(device, uniformBuffers[i], nullptr);
            vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
        }

        vkDestroyDescriptorPool(device, descriptorPool, nullptr);

        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

        for (size_t i = 0; i < indexBuffer.size(); i++) {
            vkDestroyBuffer(device, indexBuffer[i], nullptr);
            vkFreeMemory(device, indexBufferMemory[i], nullptr);

            vkDestroyBuffer(device, vertexBuffer[i], nullptr);
            vkFreeMemory(device, vertexBufferMemory[i], nullptr);
        }

        vkDestroyPipeline(device, DefaultgraphicsPipeline, nullptr);
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        vkDestroyRenderPass(device, renderPass, nullptr);

        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(device, swapChain, nullptr);
        vkDestroyDevice(device, nullptr);

        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
    }

    QueueFamilyIndices Vulkan::findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }

    void switchError(VkResult s) {
        switch (s) {
        case VK_NOT_READY:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_NOT_READY: A fence or query has not yet completed." << std::endl;
            break;
        case VK_TIMEOUT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_TIMEOUT: A wait operation has not completed in the specified time." << std::endl;
            break;
        case VK_EVENT_SET:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_EVENT_SET: An event is signaled." << std::endl;
            break;
        case VK_EVENT_RESET:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_EVENT_RESET: An event is unsignaled." << std::endl;
            break;
        case VK_INCOMPLETE:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_INCOMPLETE: A return array was too small for the result." << std::endl;
            break;
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_OUT_OF_HOST_MEMORY: A host memory allocation has failed." << std::endl;
            break;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_OUT_OF_DEVICE_MEMORY: A device memory allocation has failed." << std::endl;
            break;
        case VK_ERROR_INITIALIZATION_FAILED:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_INITIALIZATION_FAILED: Initialization of an object could not be completed for implementation-specific reasons." << std::endl;
            break;
        case VK_ERROR_DEVICE_LOST:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_DEVICE_LOST: The logical or physical device has been lost." << std::endl;
            break;
        case VK_ERROR_MEMORY_MAP_FAILED:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_MEMORY_MAP_FAILED: Mapping of a memory object has failed." << std::endl;
            break;
        case VK_ERROR_LAYER_NOT_PRESENT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_LAYER_NOT_PRESENT: A requested layer is not present or could not be loaded." << std::endl;
            break;
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_EXTENSION_NOT_PRESENT: A requested extension is not supported." << std::endl;
            break;
        case VK_ERROR_FEATURE_NOT_PRESENT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_FEATURE_NOT_PRESENT: A requested feature is not supported." << std::endl;
            break;
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_INCOMPATIBLE_DRIVER: The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons." << std::endl;
            break;
        case VK_ERROR_TOO_MANY_OBJECTS:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_TOO_MANY_OBJECTS: Too many objects of the type have already been created." << std::endl;
            break;
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_FORMAT_NOT_SUPPORTED: A requested format is not supported on this device." << std::endl;
            break;
        case VK_ERROR_FRAGMENTED_POOL:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_FRAGMENTED_POOL: A pool allocation has failed due to fragmentation of the pool's memory." << std::endl;
            break;
        case VK_ERROR_UNKNOWN:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_UNKNOWN: An unknown error occurred." << std::endl;
            break;
        case VK_ERROR_OUT_OF_POOL_MEMORY:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_OUT_OF_POOL_MEMORY: A pool memory allocation has failed." << std::endl;
            break;
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_INVALID_EXTERNAL_HANDLE: An external handle is not a valid handle." << std::endl;
            break;
        case VK_ERROR_FRAGMENTATION_EXT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_FRAGMENTATION_EXT: A descriptor pool creation has failed due to fragmentation." << std::endl;
            break;
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: An opaque capture address is not valid." << std::endl;
            break;
        case VK_ERROR_SURFACE_LOST_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_SURFACE_LOST_KHR: The surface is no longer available." << std::endl;
            break;
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: The requested window is already in use by Vulkan or another API in a manner which prevents it from being used again." << std::endl;
            break;
        case VK_SUBOPTIMAL_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_SUBOPTIMAL_KHR: A swapchain no longer matches the surface properties exactly, but can still be used to present to the surface successfully." << std::endl;
            break;
        case VK_ERROR_OUT_OF_DATE_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_OUT_OF_DATE_KHR: A surface has changed in such a way that it is no longer compatible with the swapchain, and further presentation requests using the swapchain will fail." << std::endl;
            break;
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: The display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents sharing an image." << std::endl;
            break;
        case VK_ERROR_VALIDATION_FAILED_EXT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_VALIDATION_FAILED_EXT: A validation layer found an error." << std::endl;
            break;
        case VK_ERROR_INVALID_SHADER_NV:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_INVALID_SHADER_NV: One or more shaders failed to compile or link." << std::endl;
            break;
        case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR: One or more parameters provided to CreateVideoSessionKHR are not within valid ranges." << std::endl;
            break;
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: Layout in DRM Format Modifier is not supported." << std::endl;
            break;
        case VK_ERROR_NOT_PERMITTED_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_NOT_PERMITTED_KHR: Requested operation is not permitted." << std::endl;
            break;
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: An operation on a swapchain created with a full-screen exclusive mode presentation type failed because the mode is no longer supported." << std::endl;
            break;
        case VK_THREAD_IDLE_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_THREAD_IDLE_KHR: A deferred operation is waiting on a thread." << std::endl;
            break;
        case VK_THREAD_DONE_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_THREAD_DONE_KHR: A deferred operation is blocked on a thread." << std::endl;
            break;
        case VK_OPERATION_DEFERRED_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_OPERATION_DEFERRED_KHR: A deferred operation was requested and no deferred operation is pending." << std::endl;
            break;
        case VK_OPERATION_NOT_DEFERRED_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_OPERATION_NOT_DEFERRED_KHR: A deferred operation is pending and a deferred operation was requested but not performed." << std::endl;
            break;
        case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_COMPRESSION_EXHAUSTED_EXT: A block of compressed data was too large to be processed or contained an invalid block." << std::endl;
            break;
        case VK_INCOMPATIBLE_SHADER_BINARY_EXT:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_INCOMPATIBLE_SHADER_BINARY_EXT: The shader binary is not compatible with one or more of the rest of the pipeline state." << std::endl;
            break;
        case VK_PIPELINE_COMPILE_REQUIRED:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_PIPELINE_COMPILE_REQUIRED: A requested pipeline creation requires compilation but the application has not made use of the pipeline compilation feedback information." << std::endl;
            break;
        case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR: The image usage is not supported by the current queue family." << std::endl;
            break;
        case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR: The video decoder is not capable of changing the video picture layout." << std::endl;
            break;
        case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR: The video decoder cannot create the requested video picture layout." << std::endl;
            break;
        case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR: The video decoder cannot create the requested video picture layout because it doesn't support it in the requested format." << std::endl;
            break;
        case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR: The video decoder cannot create the requested video picture layout because it doesn't support the requested codec." << std::endl;
            break;
        case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR: The video decoder cannot create the requested video picture layout because it doesn't support the requested standard version." << std::endl;
            break;
        case VK_RESULT_MAX_ENUM:
            std::cout << "[Hypa::Core::Vulkan] Error: VK_RESULT_MAX_ENUM: Maximum value of an enumeration." << std::endl;
            break;
        default:
            std::cout << "[Hypa::Core::Vulkan] Error: Unknown Vulkan error code: " << s << std::endl;
            break;
        }
    }

    bool Vulkan::isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device);

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    bool Vulkan::checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    int Vulkan::rateDeviceSuitability(VkPhysicalDevice device) {

        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        QueueFamilyIndices indices = findQueueFamilies(device);

        int score = 0;

        // Discrete GPUs have a significant performance advantage
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            score += 1000;
        }

        // Maximum possible size of textures affects graphics quality
        score += deviceProperties.limits.maxImageDimension2D;

        // Application can't function without geometry shaders
        if (!deviceFeatures.geometryShader) {
            score = 0;
            return 0;
        }

        if (!indices.isComplete()) {
            score = 0;
            return 0;
        }

        if (!isDeviceSuitable(device)) {
            score = 0;
            return 0;
        }

        log.Info((std::string)deviceProperties.deviceName + (std::string)": " + std::to_string(score) + (std::string)" Points.", "[Hypa::Core::Vulkan] ");

        return score;
    }

    SwapChainSupportDetails Vulkan::querySwapChainSupport(VkPhysicalDevice device) {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    VkSurfaceFormatKHR Vulkan::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR Vulkan::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D Vulkan::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        }
        else {
            int width, height;
            glfwGetFramebufferSize(pWindow->GetWindow(), &width, &height);

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }

    void Vulkan::createInstance() {
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "New Hypa Game";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Hypa";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create instance!");
        }
    }

    void Vulkan::setupDebugMessenger() {
        if (!enableValidationLayers) {

            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            populateDebugMessengerCreateInfo(createInfo);

            if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
                throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to set up debug messenger!");
            }
        }
    }

    void Vulkan::createSurface() {
        uint32_t count = 0;
        glfwGetRequiredInstanceExtensions(&count);

        std::cout << "Required Instance Extensions: " << count << "\n";

        VkResult s = glfwCreateWindowSurface(instance, pWindow->GetWindow(), nullptr, &surface);
        if (s != VK_SUCCESS) {
            switchError(s);
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create window surface!");
        }
    }

    void Vulkan::pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        std::multimap<int, VkPhysicalDevice> candidates;

        for (const auto& device : devices) {
            int score = rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        // Check if the best candidate is suitable at all
        if (candidates.rbegin()->first > 0) {
            physicalDevice = candidates.rbegin()->second;
        }
        else {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to find a suitable GPU!");
        }
    }

    void Vulkan::createLogicalDevice() {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create logical device!");
        }

        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
    }

    void Vulkan::createSwapChain() {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
        uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0; // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }

    void Vulkan::createImageViews() {
        swapChainImageViews.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = swapChainImageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create image views!");
            }
        }
    }

    void Vulkan::CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) {
        std::pair<VkShaderModule, VkShaderModule> a = Create_VulkanShader(VertShaderPath.c_str(), FragShaderPath.c_str());
        Shaders.insert(std::make_pair(name, std::make_tuple(a.first, a.second, UniformBufferObject())));
    }

    void Vulkan::RemoveShader(std::string name) {
        auto it = Shaders.find(name);
        if (it != Shaders.end()) {
            Shaders.erase(it);
        }
        else {
            std::cout << name << " not found in the map." << std::endl;
        }
    }

    std::tuple<VkShaderModule, VkShaderModule, UniformBufferObject> Vulkan::GetShader(std::string name) {
        return Shaders[name];
    }

    std::pair<VkShaderModule, VkShaderModule> Vulkan::Create_VulkanShader(const char* fname, const char* fgname) {

        std::ifstream file(fname, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = buffer.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(buffer.data());

        VkShaderModule vertShader;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &vertShader) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create Vertex shader module!");
        }

        std::ifstream filefrag(fgname, std::ios::ate | std::ios::binary);

        if (!filefrag.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSizefrag = (size_t)filefrag.tellg();
        std::vector<char> bufferfrag(fileSizefrag);

        filefrag.seekg(0);
        filefrag.read(bufferfrag.data(), fileSizefrag);

        filefrag.close();

        VkShaderModuleCreateInfo createInfoFrag{};
        createInfoFrag.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfoFrag.codeSize = bufferfrag.size();
        createInfoFrag.pCode = reinterpret_cast<const uint32_t*>(bufferfrag.data());

        VkShaderModule fragShader;
        if (vkCreateShaderModule(device, &createInfoFrag, nullptr, &fragShader) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create Fragment shader module!");
        }

        return std::make_pair(vertShader, fragShader);
    }

    void Vulkan::ChangeShader(std::string name) {
        CurrentShaderName = name;
        ShaderChanged = true;
    }

    VkPipeline Vulkan::createGraphicsPipeline(VkViewport viewport) {
        std::tuple<VkShaderModule, VkShaderModule, UniformBufferObject> ShaderModule = GetShader(CurrentShaderName);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = std::get<0>(ShaderModule);
        vertShaderStageInfo.pName = "main";
        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = std::get<1>(ShaderModule);
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        auto bindingDescription = getBindingDescription();
        auto attributeDescriptions = getAttributeDescriptions();

        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.scissorCount = 1;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        std::vector<VkDynamicState> dynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo dynamicState{};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
        dynamicState.pDynamicStates = dynamicStates.data();

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
        std::cout << "\n" << pushConstantRanges[currentFrame].size() << "\n";
        if (pushConstantRanges[currentFrame].size() == 0) {
            pipelineLayoutInfo.pushConstantRangeCount = 0;
            pipelineLayoutInfo.pPushConstantRanges = nullptr;
        }
        else {
            pipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges[currentFrame].size();
            pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges[currentFrame].data();
        }

        if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create pipeline layout!");
        }

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;

        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = nullptr; // Optional
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = &dynamicState;

        pipelineInfo.layout = pipelineLayout;

        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
        pipelineInfo.basePipelineIndex = -1; // Optional

        VkPipeline graphicsPipelinaae;
        VkResult a = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipelinaae);
        if (a != VK_SUCCESS) {
            switchError(a);
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create graphics pipeline!");
        }

        return graphicsPipelinaae;
    }

    void Vulkan::createRenderPass() {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = swapChainImageFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }

    void Vulkan::createFramebuffers() {
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            VkImageView attachments[] = {
                swapChainImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create framebuffer!");
            }
        }
    }

    void Vulkan::createCommandPool() {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create command pool!");
        }
    }

    void Vulkan::createCommandBuffers() {
        commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

        if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to allocate command buffers!");
        }
    }

    void Vulkan::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderPass;
        renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapChainExtent;
        VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;
        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, DefaultgraphicsPipeline);

        OtherHalfUpdateUniform();

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapChainExtent.width;
        viewport.height = (float)swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = swapChainExtent;
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

        for (size_t i = 0; i < vertexBuffer.size(); i++) {
            VkBuffer vertexBuffers[] = { vertexBuffer[i]};
            VkDeviceSize offsets[] = { 0 };
            vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

            vkCmdBindIndexBuffer(commandBuffer, indexBuffer[i], 0, VK_INDEX_TYPE_UINT16);

            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[currentFrame], 0, nullptr);
            vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(IndicesSize[i]), 1, 0, 0, 0);
        }

        vkCmdEndRenderPass(commandBuffer);

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to record command buffer!");
        }
    }

    void Vulkan::createSyncObjects() {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {

                throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create semaphores!");
            }
        }
    }

    std::string Vulkan::GetCurrentShaderName() {
        return CurrentShaderName;
    }

    void Vulkan::updateUniformBuffer(uint32_t currentImage) {

        std::tuple<VkShaderModule, VkShaderModule, UniformBufferObject> tup = GetShader(CurrentShaderName);

        UniformBufferObject ubo = std::get<2>(tup);

        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);

        ubo.proj[1][1] *= -1;

        VkDeviceSize bufferSize = sizeof(UniformBufferObject);

        vkMapMemory(device, uniformBuffersMemory[currentImage], 0, bufferSize, 0, &uniformBuffersMapped[currentImage]);
        std::memcpy(uniformBuffersMapped[currentImage], &ubo.model, sizeof(ubo.model));
        std::memcpy(static_cast<char*>(uniformBuffersMapped[currentImage]) + sizeof(ubo.model), &ubo.view, sizeof(ubo.view));
        std::memcpy(static_cast<char*>(uniformBuffersMapped[currentImage]) + sizeof(ubo.model) + sizeof(ubo.view), &ubo.proj, sizeof(ubo.proj));
        vkUnmapMemory(device, uniformBuffersMemory[currentImage]);

        // Pass custom arguments to the shader
        Uniformoffset = sizeof(ubo.model) + sizeof(ubo.view) + sizeof(ubo.proj);

        size_t offset = Uniformoffset;

        for (size_t i = 0; i < ubo.CustomArgs.size(); ++i) {
            std::visit([&](auto&& value) {
                using T = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<T, int>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(int);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(int);
                }
                else if constexpr (std::is_same_v<T, float>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame]; // 192
                    pushConstantRange.size = sizeof(float); // 4
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(float);
                }
                else if constexpr (std::is_same_v<T, double>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(float);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(float);
                }
                else if constexpr (std::is_same_v<T, glm::mat2>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat2);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat2);
                }
                else if constexpr (std::is_same_v<T, glm::mat2x2>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat2x2);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat2x2);
                }
                else if constexpr (std::is_same_v<T, glm::mat2x3>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat2x3);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat2x3);
                }
                else if constexpr (std::is_same_v<T, glm::mat2x4>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat2x4);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat2x4);
                }
                else if constexpr (std::is_same_v<T, glm::mat3>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat3);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat3);
                }
                else if constexpr (std::is_same_v<T, glm::mat3x2>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat3x2);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat3x2);
                }
                else if constexpr (std::is_same_v<T, glm::mat3x3>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat3x3);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat3x3);
                }
                else if constexpr (std::is_same_v<T, glm::mat3x4>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat3x4);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat3x4);
                }
                else if constexpr (std::is_same_v<T, glm::mat4>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat4);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat4);
                }
                else if constexpr (std::is_same_v<T, glm::mat4x2>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat4x2);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat4x2);
                }
                else if constexpr (std::is_same_v<T, glm::mat4x3>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat4x3);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat4x3);
                }
                else if constexpr (std::is_same_v<T, glm::mat4x4>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::mat4x4);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::mat4x4);
                }
                else if constexpr (std::is_same_v<T, glm::vec1>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::vec1);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::vec1);
                }
                else if constexpr (std::is_same_v<T, glm::vec2>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::vec2);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::vec2);
                }
                else if constexpr (std::is_same_v<T, glm::vec3>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::vec3);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::vec3);
                }
                else if constexpr (std::is_same_v<T, glm::vec4>) {
                    VkPushConstantRange pushConstantRange{};
                    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                    pushConstantRange.offset = pushConstantRangesOffset[currentFrame];
                    pushConstantRange.size = sizeof(glm::vec4);
                    pushConstantRanges[currentFrame].push_back(pushConstantRange);
                    pushConstantRangesOffset[currentFrame] += sizeof(glm::vec4);
                }
                // Add more type handlers as needed
                }, ubo.CustomArgs[i]);
        }

        DefaultgraphicsPipeline = createGraphicsPipeline(viewport);

        
    }

    void Vulkan::OtherHalfUpdateUniform() {
        std::tuple<VkShaderModule, VkShaderModule, UniformBufferObject> tup = GetShader(CurrentShaderName);

        UniformBufferObject ubo = std::get<2>(tup);

        size_t offset = Uniformoffset;

        for (size_t i = 0; i < ubo.CustomArgs.size(); ++i) {
            std::visit([&](auto&& value) {
                using T = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<T, int>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(int), &value);
                    offset += sizeof(int);
                }
                else if constexpr (std::is_same_v<T, float>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(float), &value);
                    offset += sizeof(float);
                }
                else if constexpr (std::is_same_v<T, double>) {
                    float temp = static_cast<float>(value);
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(float), &temp);
                    offset += sizeof(float);
                }
                else if constexpr (std::is_same_v<T, glm::mat2>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat2), &value);
                    offset += sizeof(glm::mat2);
                }
                else if constexpr (std::is_same_v<T, glm::mat2x2>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat2x2), &value);
                    offset += sizeof(glm::mat2x2);
                }
                else if constexpr (std::is_same_v<T, glm::mat2x3>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat2x3), &value);
                    offset += sizeof(glm::mat2x3);
                }
                else if constexpr (std::is_same_v<T, glm::mat2x4>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat2x4), &value);
                    offset += sizeof(glm::mat2x4);
                }
                else if constexpr (std::is_same_v<T, glm::mat3>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat3), &value);
                    offset += sizeof(glm::mat3);
                }
                else if constexpr (std::is_same_v<T, glm::mat3x2>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat3x2), &value);
                    offset += sizeof(glm::mat3x2);
                }
                else if constexpr (std::is_same_v<T, glm::mat3x3>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat3x3), &value);
                    offset += sizeof(glm::mat3x3);
                }
                else if constexpr (std::is_same_v<T, glm::mat3x4>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat3x4), &value);
                    offset += sizeof(glm::mat3x4);
                }
                else if constexpr (std::is_same_v<T, glm::mat4>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat4), &value);
                    offset += sizeof(glm::mat4);
                }
                else if constexpr (std::is_same_v<T, glm::mat4x2>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat4x2), &value);
                    offset += sizeof(glm::mat4x2);
                }
                else if constexpr (std::is_same_v<T, glm::mat4x3>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat4x3), &value);
                    offset += sizeof(glm::mat4x3);
                }
                else if constexpr (std::is_same_v<T, glm::mat4x4>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::mat4x4), &value);
                    offset += sizeof(glm::mat4x4);
                }
                else if constexpr (std::is_same_v<T, glm::vec1>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::vec1), &value);
                    offset += sizeof(glm::vec1);
                }
                else if constexpr (std::is_same_v<T, glm::vec2>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::vec2), &value);
                    offset += sizeof(glm::vec2);
                }
                else if constexpr (std::is_same_v<T, glm::vec3>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::vec3), &value);
                    offset += sizeof(glm::vec3);
                }
                else if constexpr (std::is_same_v<T, glm::vec4>) {
                    vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, offset, sizeof(glm::vec4), &value);
                    offset += sizeof(glm::vec4);
                }
                // Add more type handlers as needed
                }, ubo.CustomArgs[i]);
        }

        pushConstantRangesOffset[currentFrame] = 0;
        pushConstantRanges[currentFrame] = { };
    }

    void Vulkan::AddUniform(std::string name, UniformBufferObject& ubo) {
        Shaders[name] = std::make_tuple(std::get<0>(Shaders[name]), std::get<1>(Shaders[name]), ubo);
    }

    void Vulkan::drawFrame() {
        vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to acquire swap chain image!");
        }

        updateUniformBuffer(currentFrame);

        // Only reset the fence if we are submitting work
        vkResetFences(device, 1, &inFlightFences[currentFrame]);

        vkResetCommandBuffer(commandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
        recordCommandBuffer(commandBuffers[currentFrame], imageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

        VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { swapChain };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            recreateSwapChain();
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to present swap chain image!");
        }

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void Vulkan::cleanupSwapChain() {
        for (size_t i = 0; i < swapChainFramebuffers.size(); i++) {
            vkDestroyFramebuffer(device, swapChainFramebuffers[i], nullptr);
        }

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            vkDestroyImageView(device, swapChainImageViews[i], nullptr);
        }

        vkDestroySwapchainKHR(device, swapChain, nullptr);
    }

    void Vulkan::recreateSwapChain() {
        int width = 0, height = 0;
        glfwGetFramebufferSize(pWindow->GetWindow(), &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(pWindow->GetWindow(), &width, &height);
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(device);

        cleanupSwapChain();

        createSwapChain();
        createImageViews();
        createFramebuffers();
    }

    uint32_t Vulkan::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to find suitable memory type!");
    }

    void Vulkan::createVertexBuffer(std::vector<Vertex> vertices) {
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t)bufferSize);
        vkUnmapMemory(device, stagingBufferMemory);

        VkBuffer vertexBuffera;
        VkDeviceMemory vertexBufferMemorya;

        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffera, vertexBufferMemorya);

        copyBuffer(stagingBuffer, vertexBuffera, bufferSize);

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);

        vertexBuffer.push_back(vertexBuffera);
        vertexBufferMemory.push_back(vertexBufferMemorya);
    }

    void Vulkan::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        VkBufferCopy copyRegion{};
        copyRegion.srcOffset = 0; // Optional
        copyRegion.dstOffset = 0; // Optional
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(graphicsQueue);

        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
    }

    void Vulkan::resize_framebuffer(bool tof) {
        framebufferResized = tof;
    }

    void resizeCallback(std::shared_ptr<Event> events, std::any rend) {
        std::cout << "Type: " << rend.type().name();
        std::any_cast<Vulkan*>(rend)->resize_framebuffer(true);
    }

    void Vulkan::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to allocate buffer memory!");
        }

        vkBindBufferMemory(device, buffer, bufferMemory, 0);
    }

    void Vulkan::createIndexBuffer(std::vector<uint16_t> indices) {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t)bufferSize);
        vkUnmapMemory(device, stagingBufferMemory);

        VkBuffer indexBuffera;
        VkDeviceMemory indexBufferMemorya;

        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffera, indexBufferMemorya);

        copyBuffer(stagingBuffer, indexBuffera, bufferSize);

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);

        indexBuffer.push_back(indexBuffera);
        indexBufferMemory.push_back(indexBufferMemorya);
        IndicesSize.push_back(indices.size());
    }

    void Vulkan::createDescriptorSetLayout() {
        VkDescriptorSetLayoutBinding uboLayoutBinding{};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;

        if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create descriptor set layout!");
        }
    }

    void Vulkan::createUniformBuffers() {
        VkDeviceSize bufferSize = sizeof(UniformBufferObject);

        uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
        uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
        uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
        }
    }

    void Vulkan::createDescriptorPool() {
        VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize.descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;

        poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to create descriptor pool!");
        }
    }

    void Vulkan::createDescriptorSets() {
        std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
        if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("[Hypa::Core::Vulkan] Error: Failed to allocate descriptor sets!");
        }

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);

            VkWriteDescriptorSet descriptorWrite{};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = descriptorSets[i];
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = 0;

            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrite.descriptorCount = 1;

            descriptorWrite.pBufferInfo = &bufferInfo;
            descriptorWrite.pImageInfo = nullptr; // Optional
            descriptorWrite.pTexelBufferView = nullptr; // Optional

            vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
        }
    }

    void Vulkan::DrawVerts(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {
        createVertexBuffer(vertices);
        createIndexBuffer(indices);
    }

    void Vulkan::OnAttach() {

        log.Warning("Vulkan Initialization Not Implemented.");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // Basic Info
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        log.Info(std::to_string(extensionCount) + " Extensions Supported.", "[Hypa::Core::Vulkan] ");

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapChainExtent.width;
        viewport.height = (float)swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        for (int i = 0; i < 2; i++) {
            pushConstantRangesOffset.push_back(0);
            pushConstantRanges.push_back({ });
        }

        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        CreateShader("Default", "vert.spv", "frag.spv");
        ChangeShader("Default");
        createDescriptorSetLayout();
        DefaultgraphicsPipeline = createGraphicsPipeline(viewport);
        createFramebuffers();
        createCommandPool();

        pEvents->AddEventListener(WindowResize, resizeCallback, this);

        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        // Init Vulkan Shaders
        // Create shader modules for vertex and fragment shaders
        // Create pipeline layout
        // Create render pass
        // Create graphics pipeline
        // Create command buffers
    }

    void Vulkan::Render() {
        log.Warning("Vulkan Rendering Not Implemented.");
        // Clear Color and Depth Buffer

        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 150.0f);
        //glm::mat4 viewMatrix = glm::lookAt(returnCamera(current_camera)->position, returnCamera(current_camera)->look_at_position, returnCamera(current_camera)->up);
        glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 cameraPosition = glm::inverse(viewMatrix)[3];

        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapChainExtent.width;
        viewport.height = (float)swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        if (ShaderChanged) {
            DefaultgraphicsPipeline = createGraphicsPipeline(viewport);
            ShaderChanged = false;
        }
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommandBuffers();
        createSyncObjects();
        createFramebuffers();
        createCommandPool();

        drawFrame();

        for (size_t i = 0; i < OLDindexBuffer.size(); i++) {
            vkDestroyBuffer(device, OLDindexBuffer[i], nullptr);
            vkFreeMemory(device, OLDindexBufferMemory[i], nullptr);

            vkDestroyBuffer(device, OLDvertexBuffer[i], nullptr);
            vkFreeMemory(device, OLDvertexBufferMemory[i], nullptr);
        }

        OLDindexBuffer = indexBuffer;
        OLDindexBufferMemory = indexBufferMemory;
        OLDvertexBuffer = vertexBuffer;
        OLDvertexBufferMemory = vertexBufferMemory;
        indexBuffer.clear();
        indexBufferMemory.clear();
        vertexBuffer.clear();
        vertexBufferMemory.clear();
        IndicesSize.clear();
    }
}