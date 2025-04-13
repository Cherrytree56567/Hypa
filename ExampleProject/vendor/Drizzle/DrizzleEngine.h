#pragma once
#ifdef Drizzle_EXPORTS
#define Drizzle_API __declspec(dllexport)
#else
#define Drizzle_API __declspec(dllimport)
#endif

#include <map>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <variant>
#include <any>
#include <optional>
#include <array>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#define UBOVariant std::variant<int, float, double, std::string, char, char*, glm::mat2, glm::mat2x2, glm::mat2x3, glm::mat2x4, glm::mat3, glm::mat3x2, glm::mat3x3, glm::mat3x4, glm::mat4, glm::mat4x2, glm::mat4x3, glm::mat4x4, glm::vec3, glm::vec1, glm::vec2, glm::vec4>

typedef struct GLFWwindow GLFWwindow;
typedef unsigned int GLuint;
#define VK_DEFINE_HANDLE(object) typedef struct object##_T* object;
#define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef struct object##_T *object;
VK_DEFINE_HANDLE(VkInstance)
VK_DEFINE_HANDLE(VkPhysicalDevice)
VK_DEFINE_HANDLE(VkDevice)
VK_DEFINE_HANDLE(VkQueue)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSemaphore)
VK_DEFINE_HANDLE(VkCommandBuffer)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkFence)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDeviceMemory)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkEvent)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkQueryPool)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBufferView)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImageView)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkShaderModule)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipelineCache)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipelineLayout)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipeline)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkRenderPass)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorSetLayout)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSampler)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorSet)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorPool)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkFramebuffer)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCommandPool)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugUtilsMessengerEXT)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSurfaceKHR)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSwapchainKHR)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImage)
typedef struct VkExtent2D {
    uint32_t    width;
    uint32_t    height;
} VkExtent2D;
typedef enum VkFormat {
    VK_FORMAT_UNDEFINED = 0,
    VK_FORMAT_R4G4_UNORM_PACK8 = 1,
    VK_FORMAT_R4G4B4A4_UNORM_PACK16 = 2,
    VK_FORMAT_B4G4R4A4_UNORM_PACK16 = 3,
    VK_FORMAT_R5G6B5_UNORM_PACK16 = 4,
    VK_FORMAT_B5G6R5_UNORM_PACK16 = 5,
    VK_FORMAT_R5G5B5A1_UNORM_PACK16 = 6,
    VK_FORMAT_B5G5R5A1_UNORM_PACK16 = 7,
    VK_FORMAT_A1R5G5B5_UNORM_PACK16 = 8,
    VK_FORMAT_R8_UNORM = 9,
    VK_FORMAT_R8_SNORM = 10,
    VK_FORMAT_R8_USCALED = 11,
    VK_FORMAT_R8_SSCALED = 12,
    VK_FORMAT_R8_UINT = 13,
    VK_FORMAT_R8_SINT = 14,
    VK_FORMAT_R8_SRGB = 15,
    VK_FORMAT_R8G8_UNORM = 16,
    VK_FORMAT_R8G8_SNORM = 17,
    VK_FORMAT_R8G8_USCALED = 18,
    VK_FORMAT_R8G8_SSCALED = 19,
    VK_FORMAT_R8G8_UINT = 20,
    VK_FORMAT_R8G8_SINT = 21,
    VK_FORMAT_R8G8_SRGB = 22,
    VK_FORMAT_R8G8B8_UNORM = 23,
    VK_FORMAT_R8G8B8_SNORM = 24,
    VK_FORMAT_R8G8B8_USCALED = 25,
    VK_FORMAT_R8G8B8_SSCALED = 26,
    VK_FORMAT_R8G8B8_UINT = 27,
    VK_FORMAT_R8G8B8_SINT = 28,
    VK_FORMAT_R8G8B8_SRGB = 29,
    VK_FORMAT_B8G8R8_UNORM = 30,
    VK_FORMAT_B8G8R8_SNORM = 31,
    VK_FORMAT_B8G8R8_USCALED = 32,
    VK_FORMAT_B8G8R8_SSCALED = 33,
    VK_FORMAT_B8G8R8_UINT = 34,
    VK_FORMAT_B8G8R8_SINT = 35,
    VK_FORMAT_B8G8R8_SRGB = 36,
    VK_FORMAT_R8G8B8A8_UNORM = 37,
    VK_FORMAT_R8G8B8A8_SNORM = 38,
    VK_FORMAT_R8G8B8A8_USCALED = 39,
    VK_FORMAT_R8G8B8A8_SSCALED = 40,
    VK_FORMAT_R8G8B8A8_UINT = 41,
    VK_FORMAT_R8G8B8A8_SINT = 42,
    VK_FORMAT_R8G8B8A8_SRGB = 43,
    VK_FORMAT_B8G8R8A8_UNORM = 44,
    VK_FORMAT_B8G8R8A8_SNORM = 45,
    VK_FORMAT_B8G8R8A8_USCALED = 46,
    VK_FORMAT_B8G8R8A8_SSCALED = 47,
    VK_FORMAT_B8G8R8A8_UINT = 48,
    VK_FORMAT_B8G8R8A8_SINT = 49,
    VK_FORMAT_B8G8R8A8_SRGB = 50,
    VK_FORMAT_A8B8G8R8_UNORM_PACK32 = 51,
    VK_FORMAT_A8B8G8R8_SNORM_PACK32 = 52,
    VK_FORMAT_A8B8G8R8_USCALED_PACK32 = 53,
    VK_FORMAT_A8B8G8R8_SSCALED_PACK32 = 54,
    VK_FORMAT_A8B8G8R8_UINT_PACK32 = 55,
    VK_FORMAT_A8B8G8R8_SINT_PACK32 = 56,
    VK_FORMAT_A8B8G8R8_SRGB_PACK32 = 57,
    VK_FORMAT_A2R10G10B10_UNORM_PACK32 = 58,
    VK_FORMAT_A2R10G10B10_SNORM_PACK32 = 59,
    VK_FORMAT_A2R10G10B10_USCALED_PACK32 = 60,
    VK_FORMAT_A2R10G10B10_SSCALED_PACK32 = 61,
    VK_FORMAT_A2R10G10B10_UINT_PACK32 = 62,
    VK_FORMAT_A2R10G10B10_SINT_PACK32 = 63,
    VK_FORMAT_A2B10G10R10_UNORM_PACK32 = 64,
    VK_FORMAT_A2B10G10R10_SNORM_PACK32 = 65,
    VK_FORMAT_A2B10G10R10_USCALED_PACK32 = 66,
    VK_FORMAT_A2B10G10R10_SSCALED_PACK32 = 67,
    VK_FORMAT_A2B10G10R10_UINT_PACK32 = 68,
    VK_FORMAT_A2B10G10R10_SINT_PACK32 = 69,
    VK_FORMAT_R16_UNORM = 70,
    VK_FORMAT_R16_SNORM = 71,
    VK_FORMAT_R16_USCALED = 72,
    VK_FORMAT_R16_SSCALED = 73,
    VK_FORMAT_R16_UINT = 74,
    VK_FORMAT_R16_SINT = 75,
    VK_FORMAT_R16_SFLOAT = 76,
    VK_FORMAT_R16G16_UNORM = 77,
    VK_FORMAT_R16G16_SNORM = 78,
    VK_FORMAT_R16G16_USCALED = 79,
    VK_FORMAT_R16G16_SSCALED = 80,
    VK_FORMAT_R16G16_UINT = 81,
    VK_FORMAT_R16G16_SINT = 82,
    VK_FORMAT_R16G16_SFLOAT = 83,
    VK_FORMAT_R16G16B16_UNORM = 84,
    VK_FORMAT_R16G16B16_SNORM = 85,
    VK_FORMAT_R16G16B16_USCALED = 86,
    VK_FORMAT_R16G16B16_SSCALED = 87,
    VK_FORMAT_R16G16B16_UINT = 88,
    VK_FORMAT_R16G16B16_SINT = 89,
    VK_FORMAT_R16G16B16_SFLOAT = 90,
    VK_FORMAT_R16G16B16A16_UNORM = 91,
    VK_FORMAT_R16G16B16A16_SNORM = 92,
    VK_FORMAT_R16G16B16A16_USCALED = 93,
    VK_FORMAT_R16G16B16A16_SSCALED = 94,
    VK_FORMAT_R16G16B16A16_UINT = 95,
    VK_FORMAT_R16G16B16A16_SINT = 96,
    VK_FORMAT_R16G16B16A16_SFLOAT = 97,
    VK_FORMAT_R32_UINT = 98,
    VK_FORMAT_R32_SINT = 99,
    VK_FORMAT_R32_SFLOAT = 100,
    VK_FORMAT_R32G32_UINT = 101,
    VK_FORMAT_R32G32_SINT = 102,
    VK_FORMAT_R32G32_SFLOAT = 103,
    VK_FORMAT_R32G32B32_UINT = 104,
    VK_FORMAT_R32G32B32_SINT = 105,
    VK_FORMAT_R32G32B32_SFLOAT = 106,
    VK_FORMAT_R32G32B32A32_UINT = 107,
    VK_FORMAT_R32G32B32A32_SINT = 108,
    VK_FORMAT_R32G32B32A32_SFLOAT = 109,
    VK_FORMAT_R64_UINT = 110,
    VK_FORMAT_R64_SINT = 111,
    VK_FORMAT_R64_SFLOAT = 112,
    VK_FORMAT_R64G64_UINT = 113,
    VK_FORMAT_R64G64_SINT = 114,
    VK_FORMAT_R64G64_SFLOAT = 115,
    VK_FORMAT_R64G64B64_UINT = 116,
    VK_FORMAT_R64G64B64_SINT = 117,
    VK_FORMAT_R64G64B64_SFLOAT = 118,
    VK_FORMAT_R64G64B64A64_UINT = 119,
    VK_FORMAT_R64G64B64A64_SINT = 120,
    VK_FORMAT_R64G64B64A64_SFLOAT = 121,
    VK_FORMAT_B10G11R11_UFLOAT_PACK32 = 122,
    VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 = 123,
    VK_FORMAT_D16_UNORM = 124,
    VK_FORMAT_X8_D24_UNORM_PACK32 = 125,
    VK_FORMAT_D32_SFLOAT = 126,
    VK_FORMAT_S8_UINT = 127,
    VK_FORMAT_D16_UNORM_S8_UINT = 128,
    VK_FORMAT_D24_UNORM_S8_UINT = 129,
    VK_FORMAT_D32_SFLOAT_S8_UINT = 130,
    VK_FORMAT_BC1_RGB_UNORM_BLOCK = 131,
    VK_FORMAT_BC1_RGB_SRGB_BLOCK = 132,
    VK_FORMAT_BC1_RGBA_UNORM_BLOCK = 133,
    VK_FORMAT_BC1_RGBA_SRGB_BLOCK = 134,
    VK_FORMAT_BC2_UNORM_BLOCK = 135,
    VK_FORMAT_BC2_SRGB_BLOCK = 136,
    VK_FORMAT_BC3_UNORM_BLOCK = 137,
    VK_FORMAT_BC3_SRGB_BLOCK = 138,
    VK_FORMAT_BC4_UNORM_BLOCK = 139,
    VK_FORMAT_BC4_SNORM_BLOCK = 140,
    VK_FORMAT_BC5_UNORM_BLOCK = 141,
    VK_FORMAT_BC5_SNORM_BLOCK = 142,
    VK_FORMAT_BC6H_UFLOAT_BLOCK = 143,
    VK_FORMAT_BC6H_SFLOAT_BLOCK = 144,
    VK_FORMAT_BC7_UNORM_BLOCK = 145,
    VK_FORMAT_BC7_SRGB_BLOCK = 146,
    VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK = 147,
    VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK = 148,
    VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK = 149,
    VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK = 150,
    VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK = 151,
    VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK = 152,
    VK_FORMAT_EAC_R11_UNORM_BLOCK = 153,
    VK_FORMAT_EAC_R11_SNORM_BLOCK = 154,
    VK_FORMAT_EAC_R11G11_UNORM_BLOCK = 155,
    VK_FORMAT_EAC_R11G11_SNORM_BLOCK = 156,
    VK_FORMAT_ASTC_4x4_UNORM_BLOCK = 157,
    VK_FORMAT_ASTC_4x4_SRGB_BLOCK = 158,
    VK_FORMAT_ASTC_5x4_UNORM_BLOCK = 159,
    VK_FORMAT_ASTC_5x4_SRGB_BLOCK = 160,
    VK_FORMAT_ASTC_5x5_UNORM_BLOCK = 161,
    VK_FORMAT_ASTC_5x5_SRGB_BLOCK = 162,
    VK_FORMAT_ASTC_6x5_UNORM_BLOCK = 163,
    VK_FORMAT_ASTC_6x5_SRGB_BLOCK = 164,
    VK_FORMAT_ASTC_6x6_UNORM_BLOCK = 165,
    VK_FORMAT_ASTC_6x6_SRGB_BLOCK = 166,
    VK_FORMAT_ASTC_8x5_UNORM_BLOCK = 167,
    VK_FORMAT_ASTC_8x5_SRGB_BLOCK = 168,
    VK_FORMAT_ASTC_8x6_UNORM_BLOCK = 169,
    VK_FORMAT_ASTC_8x6_SRGB_BLOCK = 170,
    VK_FORMAT_ASTC_8x8_UNORM_BLOCK = 171,
    VK_FORMAT_ASTC_8x8_SRGB_BLOCK = 172,
    VK_FORMAT_ASTC_10x5_UNORM_BLOCK = 173,
    VK_FORMAT_ASTC_10x5_SRGB_BLOCK = 174,
    VK_FORMAT_ASTC_10x6_UNORM_BLOCK = 175,
    VK_FORMAT_ASTC_10x6_SRGB_BLOCK = 176,
    VK_FORMAT_ASTC_10x8_UNORM_BLOCK = 177,
    VK_FORMAT_ASTC_10x8_SRGB_BLOCK = 178,
    VK_FORMAT_ASTC_10x10_UNORM_BLOCK = 179,
    VK_FORMAT_ASTC_10x10_SRGB_BLOCK = 180,
    VK_FORMAT_ASTC_12x10_UNORM_BLOCK = 181,
    VK_FORMAT_ASTC_12x10_SRGB_BLOCK = 182,
    VK_FORMAT_ASTC_12x12_UNORM_BLOCK = 183,
    VK_FORMAT_ASTC_12x12_SRGB_BLOCK = 184,
    VK_FORMAT_G8B8G8R8_422_UNORM = 1000156000,
    VK_FORMAT_B8G8R8G8_422_UNORM = 1000156001,
    VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM = 1000156002,
    VK_FORMAT_G8_B8R8_2PLANE_420_UNORM = 1000156003,
    VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM = 1000156004,
    VK_FORMAT_G8_B8R8_2PLANE_422_UNORM = 1000156005,
    VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM = 1000156006,
    VK_FORMAT_R10X6_UNORM_PACK16 = 1000156007,
    VK_FORMAT_R10X6G10X6_UNORM_2PACK16 = 1000156008,
    VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 = 1000156009,
    VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = 1000156010,
    VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = 1000156011,
    VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = 1000156012,
    VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = 1000156013,
    VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = 1000156014,
    VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = 1000156015,
    VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = 1000156016,
    VK_FORMAT_R12X4_UNORM_PACK16 = 1000156017,
    VK_FORMAT_R12X4G12X4_UNORM_2PACK16 = 1000156018,
    VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 = 1000156019,
    VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = 1000156020,
    VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = 1000156021,
    VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = 1000156022,
    VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = 1000156023,
    VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = 1000156024,
    VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = 1000156025,
    VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = 1000156026,
    VK_FORMAT_G16B16G16R16_422_UNORM = 1000156027,
    VK_FORMAT_B16G16R16G16_422_UNORM = 1000156028,
    VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM = 1000156029,
    VK_FORMAT_G16_B16R16_2PLANE_420_UNORM = 1000156030,
    VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM = 1000156031,
    VK_FORMAT_G16_B16R16_2PLANE_422_UNORM = 1000156032,
    VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM = 1000156033,
    VK_FORMAT_G8_B8R8_2PLANE_444_UNORM = 1000330000,
    VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16 = 1000330001,
    VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16 = 1000330002,
    VK_FORMAT_G16_B16R16_2PLANE_444_UNORM = 1000330003,
    VK_FORMAT_A4R4G4B4_UNORM_PACK16 = 1000340000,
    VK_FORMAT_A4B4G4R4_UNORM_PACK16 = 1000340001,
    VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK = 1000066000,
    VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK = 1000066001,
    VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK = 1000066002,
    VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK = 1000066003,
    VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK = 1000066004,
    VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK = 1000066005,
    VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK = 1000066006,
    VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK = 1000066007,
    VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK = 1000066008,
    VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK = 1000066009,
    VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK = 1000066010,
    VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK = 1000066011,
    VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK = 1000066012,
    VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK = 1000066013,
    VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG = 1000054000,
    VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG = 1000054001,
    VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG = 1000054002,
    VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG = 1000054003,
    VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG = 1000054004,
    VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG = 1000054005,
    VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG = 1000054006,
    VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG = 1000054007,
    VK_FORMAT_R16G16_S10_5_NV = 1000464000,
    VK_FORMAT_A1B5G5R5_UNORM_PACK16_KHR = 1000470000,
    VK_FORMAT_A8_UNORM_KHR = 1000470001,
    VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK,
    VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK,
    VK_FORMAT_G8B8G8R8_422_UNORM_KHR = VK_FORMAT_G8B8G8R8_422_UNORM,
    VK_FORMAT_B8G8R8G8_422_UNORM_KHR = VK_FORMAT_B8G8R8G8_422_UNORM,
    VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
    VK_FORMAT_G8_B8R8_2PLANE_420_UNORM_KHR = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
    VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
    VK_FORMAT_G8_B8R8_2PLANE_422_UNORM_KHR = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
    VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
    VK_FORMAT_R10X6_UNORM_PACK16_KHR = VK_FORMAT_R10X6_UNORM_PACK16,
    VK_FORMAT_R10X6G10X6_UNORM_2PACK16_KHR = VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
    VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
    VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
    VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
    VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
    VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
    VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
    VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
    VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
    VK_FORMAT_R12X4_UNORM_PACK16_KHR = VK_FORMAT_R12X4_UNORM_PACK16,
    VK_FORMAT_R12X4G12X4_UNORM_2PACK16_KHR = VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
    VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
    VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
    VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
    VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
    VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
    VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
    VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
    VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
    VK_FORMAT_G16B16G16R16_422_UNORM_KHR = VK_FORMAT_G16B16G16R16_422_UNORM,
    VK_FORMAT_B16G16R16G16_422_UNORM_KHR = VK_FORMAT_B16G16R16G16_422_UNORM,
    VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
    VK_FORMAT_G16_B16R16_2PLANE_420_UNORM_KHR = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
    VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
    VK_FORMAT_G16_B16R16_2PLANE_422_UNORM_KHR = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
    VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
    VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT = VK_FORMAT_G8_B8R8_2PLANE_444_UNORM,
    VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16,
    VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16,
    VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT = VK_FORMAT_G16_B16R16_2PLANE_444_UNORM,
    VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT = VK_FORMAT_A4R4G4B4_UNORM_PACK16,
    VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT = VK_FORMAT_A4B4G4R4_UNORM_PACK16,
    VK_FORMAT_MAX_ENUM = 0x7FFFFFFF
} VkFormat;

namespace Drizzle {

	/*
	* Logging
	*/

	class Logging {
	public:
		Drizzle_API Logging();

		Drizzle_API void Error(std::string message, std::string who = "[Drizzle::Core] ");
		Drizzle_API void Warning(std::string message, std::string who = "[Drizzle::Core] ");
		Drizzle_API void Info(std::string message, std::string who = "[Drizzle::Core] ");
	};

	/*
	* Flags
	*/

	class Flags {
	public:
		Drizzle_API Flags();

		Drizzle_API void AddFlag(const std::string& name, std::variant<int*, double*, std::string*, bool*> variable);

		Drizzle_API void ChangeFlag(const std::string& name, std::variant<int, double, std::string, bool> value);

		Drizzle_API std::variant<int, double, std::string, bool> GetFlag(const std::string& name);

	private:
		std::unordered_map<std::string, std::variant<int*, double*, std::string*, bool*>> flags;
		Logging log;
	};

	/*
	* Event System
	*/

    enum EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        ObjectMoved
    };

    class Event {
    public:
        Drizzle_API virtual ~Event() = default;

        bool Handled = false;

        Drizzle_API virtual EventType GetEventType() = 0;
    };

    class EventSystem {
    public:
        Drizzle_API EventSystem();

        typedef void (*EventCallback)(std::shared_ptr<Event> events, std::any);

        Drizzle_API void AddEvent(std::shared_ptr<Event> newEvent);
        Drizzle_API std::shared_ptr<Event> GetEvent(EventType eventType);
        Drizzle_API void RemoveHandledEvents();
        Drizzle_API bool isUnhandledEvent(EventType eventType);
        Drizzle_API void ResetEvents() { events.clear(); }
        Drizzle_API void AddEventListener(EventType eventType, EventCallback callback, std::any a = NULL);
        Drizzle_API void RemoveEventListener(EventType eventType, EventCallback callback);
        Drizzle_API void DispatchEvent();


    private:
        std::vector<std::shared_ptr<Event>> events;
        std::unordered_map<EventType, std::vector<std::pair<EventCallback, std::any>>> eventCallbacks;
    };

    /*
    * Events
    */

    class WindowResizeEvent : public Event {
    public:
        Drizzle_API WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

        Drizzle_API unsigned int GetWidth() const { return m_Width; }
        Drizzle_API unsigned int GetHeight() const { return m_Height; }

        Drizzle_API EventType GetEventType() override { return EventType::WindowResize; }
    private:
        unsigned int m_Width, m_Height;
    };

    class WindowMoveEvent : public Event {
    public:
        Drizzle_API WindowMoveEvent(unsigned int x, unsigned int y) : m_x(x), m_y(y) {}

        Drizzle_API unsigned int GetWidth() const { return m_x; }
        Drizzle_API unsigned int GetHeight() const { return m_y; }
        Drizzle_API EventType GetEventType() override { return EventType::WindowMoved; }
    private:
        unsigned int m_x, m_y;
    };

    class WindowFocusEvent : public Event {
    public:
        Drizzle_API WindowFocusEvent(bool isFocused) : m_is_focused(isFocused) {}

        Drizzle_API bool IsFocused() const { return m_is_focused; }
        Drizzle_API EventType GetEventType() override { return EventType::WindowFocus; }
    private:
        bool m_is_focused;
    };

    class WindowCloseEvent : public Event {
    public:
        Drizzle_API WindowCloseEvent() = default;

        Drizzle_API EventType GetEventType() override { return EventType::WindowClose; }
    };

    class AppTickEvent : public Event {
    public:
        Drizzle_API AppTickEvent() = default;

        Drizzle_API EventType GetEventType() override { return EventType::AppTick; }
    };

    class AppUpdateEvent : public Event {
    public:
        Drizzle_API AppUpdateEvent() = default;

        Drizzle_API EventType GetEventType() override { return EventType::AppUpdate; }
    };

    class AppRenderEvent : public Event {
    public:
        Drizzle_API AppRenderEvent() = default;

        Drizzle_API EventType GetEventType() override { return EventType::AppRender; }
    };

    /*
    * From GLFW.
    */
    enum KeyCode {
        Space = 32,
        Apostrophe = 39,
        Comma = 44,
        Minus = 45,
        Period = 46,
        Slash = 47,

        D0 = 48,
        D1 = 49,
        D2 = 50,
        D3 = 51,
        D4 = 52,
        D5 = 53,
        D6 = 54,
        D7 = 55,
        D8 = 56,
        D9 = 57,

        Semicolon = 59,
        Equal = 61,

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftBracket = 91,
        Backslash = 92,
        RightBracket = 93,
        GraveAccent = 96,

        World1 = 161,
        World2 = 162,

        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,

        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,
        Menu = 348
    };

    class KeyPressedEvent : public Event {
    public:
        Drizzle_API KeyPressedEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

        Drizzle_API KeyCode GetKeyCode() { return m_KeyCode; }

        Drizzle_API EventType GetEventType() override { return EventType::KeyPressed; }
    private:
        KeyCode m_KeyCode;
    };

    class KeyReleasedEvent : public Event {
    public:
        Drizzle_API KeyReleasedEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

        Drizzle_API KeyCode GetKeyCode() { return m_KeyCode; }

        Drizzle_API EventType GetEventType() override { return EventType::KeyReleased; }
    private:
        KeyCode m_KeyCode;
    };

    enum MouseCode {
        Button1 = 0,
        Button2 = 1,
        Button3 = 2,
        Button4 = 3,
        Button5 = 4,
        Button6 = 5,
        Button7 = 6,
        Button8 = 7,

        ButtonLast = Button8,
        ButtonLeft = Button1,
        ButtonRight = Button2,
        ButtonMiddle = Button3
    };

    class MouseMovedEvent : public Event {
    public:
        Drizzle_API MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}

        Drizzle_API float GetX() const { return m_MouseX; }
        Drizzle_API float GetY() const { return m_MouseY; }

        Drizzle_API EventType GetEventType() override { return EventType::MouseMoved; }
    private:
        float m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent : public Event {
    public:
        Drizzle_API MouseScrolledEvent(const float xOffset, const float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

        Drizzle_API float GetXOffset() const { return m_XOffset; }
        Drizzle_API float GetYOffset() const { return m_YOffset; }

        Drizzle_API EventType GetEventType() override { return EventType::MouseScrolled; }
    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonPressedEvent : public Event {
    public:
        Drizzle_API MouseButtonPressedEvent(const MouseCode button) : m_Button(button) {}

        Drizzle_API MouseCode GetMouseButton() const { return m_Button; }

        Drizzle_API EventType GetEventType() override { return EventType::MouseButtonPressed; }
    private:
        MouseCode m_Button;
    };

    class MouseButtonReleasedEvent : public Event {
    public:
        Drizzle_API MouseButtonReleasedEvent(const MouseCode button) : m_Button(button) {}

        Drizzle_API MouseCode GetMouseButton() const { return m_Button; }

        Drizzle_API EventType GetEventType() override { return EventType::MouseButtonReleased; }
    private:
        MouseCode m_Button;
    };

	/*
	* RenderingAPI
	*/

    struct Vertex {
        glm::vec3 pos;
        glm::vec3 TexCoords;
        glm::vec3 Normals;
    };

    struct PushConstants {
        glm::vec4 data1;
        glm::vec4 data2;
        glm::vec4 data3;
        glm::vec4 data4;
    };

    struct APIObject {
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;
        glm::mat4 modelMatrix;
        glm::vec3 minBound;
        glm::vec3 maxBound;
        glm::vec3 center;
        std::string name;
        std::string shaderName;
        std::string textureName;
        bool hidden = false;
    };

    class RenderingAPI {
    public:
        Drizzle_API RenderingAPI() {}

        Drizzle_API virtual void OnAttach() {}
        Drizzle_API virtual void OnDetach() {}
        Drizzle_API virtual void RenderBefore() {}
        Drizzle_API virtual void RenderAfter() {}
        Drizzle_API virtual void Render3D(std::vector<APIObject> objs) {}

        Drizzle_API virtual void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) {}
        Drizzle_API virtual void RemoveShader(std::string name) {}
        Drizzle_API virtual void ChangeShader(std::string name) {}
        Drizzle_API virtual std::string GetCurrentShaderName() { return ""; }

        Drizzle_API virtual void CreateTexture(std::string name, std::string TexturePath) {}
        Drizzle_API virtual void RemoveTexture(std::string name) {}
        Drizzle_API virtual void ChangeTexture(std::string name) {}
        Drizzle_API virtual std::string GetCurrentTextureName() { return ""; }

        Drizzle_API virtual void AddObject(APIObject obj) {}
        Drizzle_API virtual void RemoveObject(std::string name) {}

        Drizzle_API virtual const std::string& GetName() const { return name; }
        Drizzle_API virtual PushConstants& GetPushConstants() { return pushConstants; }

    private:
        Flags flags;
        std::string name;
        PushConstants pushConstants;
    };

    class RenderingAPISystem {
    public:
        Drizzle_API RenderingAPISystem();

        Drizzle_API void AddAPI(std::shared_ptr<RenderingAPI> API);
        Drizzle_API void RemoveAPIByName(const std::string& name);
        Drizzle_API std::shared_ptr<RenderingAPI> GetCurrentRenderingAPI();
        Drizzle_API void SwitchRenderingAPI(std::string name);
        Drizzle_API std::string GetCurrentRenderingAPIName();

    private:
        std::vector<std::shared_ptr<RenderingAPI>> renderingAPIS;
        std::string CurrentRenderingAPI;
    };

	/*
	* Window
	*/

    class Window {
    public:
        Drizzle_API Window(std::shared_ptr<EventSystem> EvSys);

        Drizzle_API GLFWwindow* GetWindow();

        Drizzle_API void Update();
        Drizzle_API void ProcessEvents();
        Drizzle_API bool shouldClose();
        Drizzle_API std::shared_ptr<Flags> GetFlags();

    private:
        int width = 800;
        int height = 600;
        std::string title = "New Drizzle Game";
        int WindowX = 100;
        int WindowY = 100;
        GLFWwindow* window;
        Logging log;
        std::shared_ptr<Flags> flags = std::make_shared<Flags>();
        std::shared_ptr<EventSystem> Events = NULL;

        std::vector<int> key_codes;
        std::vector<int> keyRel_codes;
        bool wasLeftMouseButtonPressed = false;
        bool wasRightMouseButtonPressed = false;
        double lastMouseX = 0.0;
        double lastMouseY = 0.0;
        double lastSMouseX = 0.0;
        double lastSMouseY = 0.0;
    };

    /*
    * Layer
    */

    class Layer {
    public:
        Drizzle_API Layer() {}

        Drizzle_API Layer(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys) : name("Layer"), pWindow(window), rAPISystem(rAPIsys) {}

        Drizzle_API virtual ~Layer() = default;
        Drizzle_API virtual void OnAttach() {}
        Drizzle_API virtual void OnDetach() {}
        Drizzle_API virtual void Render() {}

        Drizzle_API virtual bool IsShown() const { return show; }
        Drizzle_API virtual const std::string& GetName() const { return name; }
        Drizzle_API virtual void SetShow(bool value) { show = value; }
    private:
        bool show = false;
        std::string name;
        std::shared_ptr<Window> pWindow = NULL;
        std::shared_ptr<RenderingAPISystem> rAPISystem = NULL;
    };

    class LayerDispatch {
    public:
        Drizzle_API void AddLayer(std::shared_ptr<Layer> layer);
        Drizzle_API void RemoveLayerByName(const std::string& name);
        Drizzle_API void ShowHideLayerByName(const std::string& name, bool show);
        Drizzle_API std::shared_ptr<Layer> GetLayer(const std::string& name);
        Drizzle_API void PushFront(const std::string& name);
        Drizzle_API void PushForward(const std::string& name);
        Drizzle_API void PushBack(const std::string& name);
        Drizzle_API void PushBackward(const std::string& name);

        Drizzle_API void DispatchLayerRender();
        Drizzle_API void DispatchLayerDetach();
        Drizzle_API void DispatchLayerAttach();

    private:
        std::vector<std::shared_ptr<Layer>> layers;
    };

    /*
    * Vulkan
    */

    class Vulkan : public RenderingAPI {
    public:
        Drizzle_API Vulkan(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events);

        Drizzle_API void OnAttach() override;
        Drizzle_API void OnDetach() override;
        Drizzle_API void RenderBefore() override;
        Drizzle_API void RenderAfter() override;
        Drizzle_API void Render3D(std::vector<APIObject> objs) override;

        Drizzle_API const std::string& GetName() const override;
        Drizzle_API void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) override;
        Drizzle_API void RemoveShader(std::string name) override;
        Drizzle_API void ChangeShader(std::string name) override;
        Drizzle_API std::string GetCurrentShaderName() override;

        Drizzle_API void CreateTexture(std::string name, std::string TexturePath) override;
        Drizzle_API void RemoveTexture(std::string name) override;

        Drizzle_API void AddObject(APIObject obj) override;
        Drizzle_API void RemoveObject(std::string name) override;

        Drizzle_API PushConstants& GetPushConstants() override { return pushConstants; }

    private:
        Flags flags;
        std::string name;
        std::string CurrentShaderName = "Default";
        Logging log;
        bool ShaderChanged = false;
        std::shared_ptr<Window> pWindow;
        std::shared_ptr<EventSystem> pEvents;
        PushConstants pushConstants;
    };

    /*
    * OpenGL
    */

    class OpenGL : public RenderingAPI {
    public:
        Drizzle_API OpenGL(std::shared_ptr<Window> window, std::shared_ptr<EventSystem> Events);

        Drizzle_API virtual void OnAttach() override;
        Drizzle_API virtual void OnDetach() override;

        Drizzle_API virtual void CreateShader(std::string name, std::string VertShaderPath, std::string FragShaderPath) override;
        Drizzle_API virtual void RemoveShader(std::string name) override;
        Drizzle_API virtual void ChangeShader(std::string name) override;
        Drizzle_API virtual std::string GetCurrentShaderName() override;

        Drizzle_API virtual void CreateTexture(std::string name, std::string TexturePath) override;
        Drizzle_API virtual void RemoveTexture(std::string name) override;
        Drizzle_API virtual void ChangeTexture(std::string name) override;
        Drizzle_API virtual std::string GetCurrentTextureName() override;

        Drizzle_API virtual const std::string& GetName() const override { return name; }

        Drizzle_API virtual PushConstants& GetPushConstants() override { return pushConstants; }

    private:
        std::tuple<unsigned int, unsigned int> GetShader(std::string name);

        Flags flags;
        std::string name;
        std::shared_ptr<Window> pWindow;
        std::shared_ptr<EventSystem> pEvents;
        Logging log;
        std::vector<GLuint> VertexArray;
        std::vector<GLuint> VertexBuffer;
        std::vector<GLuint> IndexBuffer;
        std::vector<std::vector<uint16_t>> Indices;
        std::string CurrentShaderName = "Default";
        std::string CurrentTextureName = "";
        bool ShaderChanged = true;
        std::map<std::string, std::tuple<unsigned int, unsigned int>> Shaders;
        std::map<std::string, unsigned int> Textures;
        PushConstants pushConstants;
    };

    /*
    * Rendering3D
    */

    class Rendering3D : public Layer {
    public:
        Drizzle_API Rendering3D(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys);

        Drizzle_API virtual ~Rendering3D() override;
        Drizzle_API virtual void OnAttach() override;
        Drizzle_API virtual void OnDetach() override;
        Drizzle_API virtual void Render() override;

        Drizzle_API virtual bool IsShown() const override;
        Drizzle_API virtual const std::string& GetName() const override;
        Drizzle_API virtual void SetShow(bool value) override;

        Drizzle_API void CreateObject(std::string name, APIObject obj);
        Drizzle_API void RemoveObject(std::string name, bool grouped = false);
        Drizzle_API APIObject& GetObject(std::string name);
        Drizzle_API void LoadOBJ(std::string name, const std::string& filePath, const std::string& mtlPath = "");
    private:
        bool show = false;
        std::string name;
        std::shared_ptr<Window> pWindow = NULL;
        std::shared_ptr<RenderingAPISystem> rAPISystem = NULL;
    };

	/*
	* App
	*/

    class App {
    public:
        Drizzle_API App();
        Drizzle_API ~App();

        Drizzle_API bool Update();

        Drizzle_API std::shared_ptr<Window> GetWindow();
        Drizzle_API std::shared_ptr<EventSystem> GetEventSystem();
        Drizzle_API std::shared_ptr<RenderingAPISystem> GetRenderingAPISystem();
        Drizzle_API std::shared_ptr<LayerDispatch> GetLayerDispatch();
        Drizzle_API std::shared_ptr<Vulkan> GetVulkan();
        Drizzle_API std::shared_ptr<OpenGL> GetOpenGL();
        Drizzle_API std::shared_ptr<Rendering3D> GetRendering3D();

    private:
        std::shared_ptr<Window> window;
        std::shared_ptr<EventSystem> Events;
        std::shared_ptr<RenderingAPISystem> rAPIsystem;
        std::shared_ptr<Vulkan> VulkanAPI;
        std::shared_ptr<OpenGL> OpenGLAPI;
        std::shared_ptr<LayerDispatch> Layerdispatch;
        std::shared_ptr<Rendering3D> Rendering3d;
    };
}