/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/vulkansc.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif








static void glad_vk_load_VKSC_VERSION_1_0(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SC_VERSION_1_0) return;
    context->GetCommandPoolMemoryConsumption = (PFN_vkGetCommandPoolMemoryConsumption) load(userptr, "vkGetCommandPoolMemoryConsumption");
    context->GetFaultData = (PFN_vkGetFaultData) load(userptr, "vkGetFaultData");
}
static void glad_vk_load_VK_VERSION_1_1(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_1) return;
    context->BindBufferMemory2 = (PFN_vkBindBufferMemory2) load(userptr, "vkBindBufferMemory2");
    context->BindImageMemory2 = (PFN_vkBindImageMemory2) load(userptr, "vkBindImageMemory2");
    context->CmdDispatchBase = (PFN_vkCmdDispatchBase) load(userptr, "vkCmdDispatchBase");
    context->CmdSetDeviceMask = (PFN_vkCmdSetDeviceMask) load(userptr, "vkCmdSetDeviceMask");
    context->CreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate) load(userptr, "vkCreateDescriptorUpdateTemplate");
    context->CreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion) load(userptr, "vkCreateSamplerYcbcrConversion");
    context->DestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate) load(userptr, "vkDestroyDescriptorUpdateTemplate");
    context->DestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion) load(userptr, "vkDestroySamplerYcbcrConversion");
    context->EnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion) load(userptr, "vkEnumerateInstanceVersion");
    context->EnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups) load(userptr, "vkEnumeratePhysicalDeviceGroups");
    context->GetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2) load(userptr, "vkGetBufferMemoryRequirements2");
    context->GetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport) load(userptr, "vkGetDescriptorSetLayoutSupport");
    context->GetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures) load(userptr, "vkGetDeviceGroupPeerMemoryFeatures");
    context->GetDeviceQueue2 = (PFN_vkGetDeviceQueue2) load(userptr, "vkGetDeviceQueue2");
    context->GetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2) load(userptr, "vkGetImageMemoryRequirements2");
    context->GetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2) load(userptr, "vkGetImageSparseMemoryRequirements2");
    context->GetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties) load(userptr, "vkGetPhysicalDeviceExternalBufferProperties");
    context->GetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties) load(userptr, "vkGetPhysicalDeviceExternalFenceProperties");
    context->GetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties) load(userptr, "vkGetPhysicalDeviceExternalSemaphoreProperties");
    context->GetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2) load(userptr, "vkGetPhysicalDeviceFeatures2");
    context->GetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2) load(userptr, "vkGetPhysicalDeviceFormatProperties2");
    context->GetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2) load(userptr, "vkGetPhysicalDeviceImageFormatProperties2");
    context->GetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2) load(userptr, "vkGetPhysicalDeviceMemoryProperties2");
    context->GetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2) load(userptr, "vkGetPhysicalDeviceProperties2");
    context->GetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2) load(userptr, "vkGetPhysicalDeviceQueueFamilyProperties2");
    context->GetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2) load(userptr, "vkGetPhysicalDeviceSparseImageFormatProperties2");
    context->TrimCommandPool = (PFN_vkTrimCommandPool) load(userptr, "vkTrimCommandPool");
    context->UpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate) load(userptr, "vkUpdateDescriptorSetWithTemplate");
}
static void glad_vk_load_VK_VERSION_1_2(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_2) return;
    context->CmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2) load(userptr, "vkCmdBeginRenderPass2");
    context->CmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount) load(userptr, "vkCmdDrawIndexedIndirectCount");
    context->CmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount) load(userptr, "vkCmdDrawIndirectCount");
    context->CmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2) load(userptr, "vkCmdEndRenderPass2");
    context->CmdNextSubpass2 = (PFN_vkCmdNextSubpass2) load(userptr, "vkCmdNextSubpass2");
    context->CreateRenderPass2 = (PFN_vkCreateRenderPass2) load(userptr, "vkCreateRenderPass2");
    context->GetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress) load(userptr, "vkGetBufferDeviceAddress");
    context->GetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress) load(userptr, "vkGetBufferOpaqueCaptureAddress");
    context->GetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress) load(userptr, "vkGetDeviceMemoryOpaqueCaptureAddress");
    context->GetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue) load(userptr, "vkGetSemaphoreCounterValue");
    context->ResetQueryPool = (PFN_vkResetQueryPool) load(userptr, "vkResetQueryPool");
    context->SignalSemaphore = (PFN_vkSignalSemaphore) load(userptr, "vkSignalSemaphore");
    context->WaitSemaphores = (PFN_vkWaitSemaphores) load(userptr, "vkWaitSemaphores");
}
static void glad_vk_load_VK_VERSION_1_3(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_3) return;
    context->CmdBeginRendering = (PFN_vkCmdBeginRendering) load(userptr, "vkCmdBeginRendering");
    context->CmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2) load(userptr, "vkCmdBindVertexBuffers2");
    context->CmdBlitImage2 = (PFN_vkCmdBlitImage2) load(userptr, "vkCmdBlitImage2");
    context->CmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2) load(userptr, "vkCmdCopyBuffer2");
    context->CmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2) load(userptr, "vkCmdCopyBufferToImage2");
    context->CmdCopyImage2 = (PFN_vkCmdCopyImage2) load(userptr, "vkCmdCopyImage2");
    context->CmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2) load(userptr, "vkCmdCopyImageToBuffer2");
    context->CmdEndRendering = (PFN_vkCmdEndRendering) load(userptr, "vkCmdEndRendering");
    context->CmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2) load(userptr, "vkCmdPipelineBarrier2");
    context->CmdResetEvent2 = (PFN_vkCmdResetEvent2) load(userptr, "vkCmdResetEvent2");
    context->CmdResolveImage2 = (PFN_vkCmdResolveImage2) load(userptr, "vkCmdResolveImage2");
    context->CmdSetCullMode = (PFN_vkCmdSetCullMode) load(userptr, "vkCmdSetCullMode");
    context->CmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable) load(userptr, "vkCmdSetDepthBiasEnable");
    context->CmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable) load(userptr, "vkCmdSetDepthBoundsTestEnable");
    context->CmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp) load(userptr, "vkCmdSetDepthCompareOp");
    context->CmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable) load(userptr, "vkCmdSetDepthTestEnable");
    context->CmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable) load(userptr, "vkCmdSetDepthWriteEnable");
    context->CmdSetEvent2 = (PFN_vkCmdSetEvent2) load(userptr, "vkCmdSetEvent2");
    context->CmdSetFrontFace = (PFN_vkCmdSetFrontFace) load(userptr, "vkCmdSetFrontFace");
    context->CmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable) load(userptr, "vkCmdSetPrimitiveRestartEnable");
    context->CmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology) load(userptr, "vkCmdSetPrimitiveTopology");
    context->CmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable) load(userptr, "vkCmdSetRasterizerDiscardEnable");
    context->CmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount) load(userptr, "vkCmdSetScissorWithCount");
    context->CmdSetStencilOp = (PFN_vkCmdSetStencilOp) load(userptr, "vkCmdSetStencilOp");
    context->CmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable) load(userptr, "vkCmdSetStencilTestEnable");
    context->CmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount) load(userptr, "vkCmdSetViewportWithCount");
    context->CmdWaitEvents2 = (PFN_vkCmdWaitEvents2) load(userptr, "vkCmdWaitEvents2");
    context->CmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2) load(userptr, "vkCmdWriteTimestamp2");
    context->CreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot) load(userptr, "vkCreatePrivateDataSlot");
    context->DestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot) load(userptr, "vkDestroyPrivateDataSlot");
    context->GetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements) load(userptr, "vkGetDeviceBufferMemoryRequirements");
    context->GetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements) load(userptr, "vkGetDeviceImageMemoryRequirements");
    context->GetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements) load(userptr, "vkGetDeviceImageSparseMemoryRequirements");
    context->GetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties) load(userptr, "vkGetPhysicalDeviceToolProperties");
    context->GetPrivateData = (PFN_vkGetPrivateData) load(userptr, "vkGetPrivateData");
    context->QueueSubmit2 = (PFN_vkQueueSubmit2) load(userptr, "vkQueueSubmit2");
    context->SetPrivateData = (PFN_vkSetPrivateData) load(userptr, "vkSetPrivateData");
}
static void glad_vk_load_VK_EXT_color_write_enable(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_color_write_enable) return;
    context->CmdSetColorWriteEnableEXT = (PFN_vkCmdSetColorWriteEnableEXT) load(userptr, "vkCmdSetColorWriteEnableEXT");
}
static void glad_vk_load_VK_EXT_debug_utils(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_debug_utils) return;
    context->CmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT) load(userptr, "vkCmdBeginDebugUtilsLabelEXT");
    context->CmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT) load(userptr, "vkCmdEndDebugUtilsLabelEXT");
    context->CmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT) load(userptr, "vkCmdInsertDebugUtilsLabelEXT");
    context->CreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT) load(userptr, "vkCreateDebugUtilsMessengerEXT");
    context->DestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) load(userptr, "vkDestroyDebugUtilsMessengerEXT");
    context->QueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT) load(userptr, "vkQueueBeginDebugUtilsLabelEXT");
    context->QueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT) load(userptr, "vkQueueEndDebugUtilsLabelEXT");
    context->QueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT) load(userptr, "vkQueueInsertDebugUtilsLabelEXT");
    context->SetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT) load(userptr, "vkSetDebugUtilsObjectNameEXT");
    context->SetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT) load(userptr, "vkSetDebugUtilsObjectTagEXT");
    context->SubmitDebugUtilsMessageEXT = (PFN_vkSubmitDebugUtilsMessageEXT) load(userptr, "vkSubmitDebugUtilsMessageEXT");
}
static void glad_vk_load_VK_EXT_direct_mode_display(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_direct_mode_display) return;
    context->ReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT) load(userptr, "vkReleaseDisplayEXT");
}
static void glad_vk_load_VK_EXT_discard_rectangles(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_discard_rectangles) return;
    context->CmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT) load(userptr, "vkCmdSetDiscardRectangleEXT");
    context->CmdSetDiscardRectangleEnableEXT = (PFN_vkCmdSetDiscardRectangleEnableEXT) load(userptr, "vkCmdSetDiscardRectangleEnableEXT");
    context->CmdSetDiscardRectangleModeEXT = (PFN_vkCmdSetDiscardRectangleModeEXT) load(userptr, "vkCmdSetDiscardRectangleModeEXT");
}
static void glad_vk_load_VK_EXT_display_control(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_display_control) return;
    context->DisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT) load(userptr, "vkDisplayPowerControlEXT");
    context->GetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT) load(userptr, "vkGetSwapchainCounterEXT");
    context->RegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT) load(userptr, "vkRegisterDeviceEventEXT");
    context->RegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT) load(userptr, "vkRegisterDisplayEventEXT");
}
static void glad_vk_load_VK_EXT_display_surface_counter(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_display_surface_counter) return;
    context->GetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT) load(userptr, "vkGetPhysicalDeviceSurfaceCapabilities2EXT");
}
static void glad_vk_load_VK_EXT_extended_dynamic_state(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_extended_dynamic_state) return;
    context->CmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT) load(userptr, "vkCmdBindVertexBuffers2EXT");
    context->CmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT) load(userptr, "vkCmdSetCullModeEXT");
    context->CmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT) load(userptr, "vkCmdSetDepthBoundsTestEnableEXT");
    context->CmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT) load(userptr, "vkCmdSetDepthCompareOpEXT");
    context->CmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT) load(userptr, "vkCmdSetDepthTestEnableEXT");
    context->CmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT) load(userptr, "vkCmdSetDepthWriteEnableEXT");
    context->CmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT) load(userptr, "vkCmdSetFrontFaceEXT");
    context->CmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT) load(userptr, "vkCmdSetPrimitiveTopologyEXT");
    context->CmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT) load(userptr, "vkCmdSetScissorWithCountEXT");
    context->CmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT) load(userptr, "vkCmdSetStencilOpEXT");
    context->CmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT) load(userptr, "vkCmdSetStencilTestEnableEXT");
    context->CmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT) load(userptr, "vkCmdSetViewportWithCountEXT");
}
static void glad_vk_load_VK_EXT_extended_dynamic_state2(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_extended_dynamic_state2) return;
    context->CmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT) load(userptr, "vkCmdSetDepthBiasEnableEXT");
    context->CmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT) load(userptr, "vkCmdSetLogicOpEXT");
    context->CmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT) load(userptr, "vkCmdSetPatchControlPointsEXT");
    context->CmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT) load(userptr, "vkCmdSetPrimitiveRestartEnableEXT");
    context->CmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT) load(userptr, "vkCmdSetRasterizerDiscardEnableEXT");
}
static void glad_vk_load_VK_EXT_external_memory_host(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_external_memory_host) return;
    context->GetMemoryHostPointerPropertiesEXT = (PFN_vkGetMemoryHostPointerPropertiesEXT) load(userptr, "vkGetMemoryHostPointerPropertiesEXT");
}
static void glad_vk_load_VK_EXT_hdr_metadata(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_hdr_metadata) return;
    context->SetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT) load(userptr, "vkSetHdrMetadataEXT");
}
static void glad_vk_load_VK_EXT_headless_surface(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_headless_surface) return;
    context->CreateHeadlessSurfaceEXT = (PFN_vkCreateHeadlessSurfaceEXT) load(userptr, "vkCreateHeadlessSurfaceEXT");
}
static void glad_vk_load_VK_EXT_image_drm_format_modifier(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_image_drm_format_modifier) return;
    context->GetImageDrmFormatModifierPropertiesEXT = (PFN_vkGetImageDrmFormatModifierPropertiesEXT) load(userptr, "vkGetImageDrmFormatModifierPropertiesEXT");
}
static void glad_vk_load_VK_EXT_line_rasterization(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_line_rasterization) return;
    context->CmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT) load(userptr, "vkCmdSetLineStippleEXT");
}
static void glad_vk_load_VK_EXT_sample_locations(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_sample_locations) return;
    context->CmdSetSampleLocationsEXT = (PFN_vkCmdSetSampleLocationsEXT) load(userptr, "vkCmdSetSampleLocationsEXT");
    context->GetPhysicalDeviceMultisamplePropertiesEXT = (PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT) load(userptr, "vkGetPhysicalDeviceMultisamplePropertiesEXT");
}
static void glad_vk_load_VK_EXT_vertex_input_dynamic_state(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_vertex_input_dynamic_state) return;
    context->CmdSetVertexInputEXT = (PFN_vkCmdSetVertexInputEXT) load(userptr, "vkCmdSetVertexInputEXT");
}
static void glad_vk_load_VK_KHR_calibrated_timestamps(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_calibrated_timestamps) return;
    context->GetCalibratedTimestampsKHR = (PFN_vkGetCalibratedTimestampsKHR) load(userptr, "vkGetCalibratedTimestampsKHR");
    context->GetPhysicalDeviceCalibrateableTimeDomainsKHR = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR) load(userptr, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");
}
static void glad_vk_load_VK_KHR_copy_commands2(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_copy_commands2) return;
    context->CmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR) load(userptr, "vkCmdBlitImage2KHR");
    context->CmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR) load(userptr, "vkCmdCopyBuffer2KHR");
    context->CmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR) load(userptr, "vkCmdCopyBufferToImage2KHR");
    context->CmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR) load(userptr, "vkCmdCopyImage2KHR");
    context->CmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR) load(userptr, "vkCmdCopyImageToBuffer2KHR");
    context->CmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR) load(userptr, "vkCmdResolveImage2KHR");
}
static void glad_vk_load_VK_KHR_display(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_display) return;
    context->CreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR) load(userptr, "vkCreateDisplayModeKHR");
    context->CreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR) load(userptr, "vkCreateDisplayPlaneSurfaceKHR");
    context->GetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR) load(userptr, "vkGetDisplayModePropertiesKHR");
    context->GetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR) load(userptr, "vkGetDisplayPlaneCapabilitiesKHR");
    context->GetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR) load(userptr, "vkGetDisplayPlaneSupportedDisplaysKHR");
    context->GetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR) load(userptr, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
    context->GetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR) load(userptr, "vkGetPhysicalDeviceDisplayPropertiesKHR");
}
static void glad_vk_load_VK_KHR_display_swapchain(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_display_swapchain) return;
    context->CreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR) load(userptr, "vkCreateSharedSwapchainsKHR");
}
static void glad_vk_load_VK_KHR_external_fence_fd(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_fence_fd) return;
    context->GetFenceFdKHR = (PFN_vkGetFenceFdKHR) load(userptr, "vkGetFenceFdKHR");
    context->ImportFenceFdKHR = (PFN_vkImportFenceFdKHR) load(userptr, "vkImportFenceFdKHR");
}
static void glad_vk_load_VK_KHR_external_memory_fd(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_memory_fd) return;
    context->GetMemoryFdKHR = (PFN_vkGetMemoryFdKHR) load(userptr, "vkGetMemoryFdKHR");
    context->GetMemoryFdPropertiesKHR = (PFN_vkGetMemoryFdPropertiesKHR) load(userptr, "vkGetMemoryFdPropertiesKHR");
}
static void glad_vk_load_VK_KHR_external_semaphore_fd(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_semaphore_fd) return;
    context->GetSemaphoreFdKHR = (PFN_vkGetSemaphoreFdKHR) load(userptr, "vkGetSemaphoreFdKHR");
    context->ImportSemaphoreFdKHR = (PFN_vkImportSemaphoreFdKHR) load(userptr, "vkImportSemaphoreFdKHR");
}
static void glad_vk_load_VK_KHR_fragment_shading_rate(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_fragment_shading_rate) return;
    context->CmdSetFragmentShadingRateKHR = (PFN_vkCmdSetFragmentShadingRateKHR) load(userptr, "vkCmdSetFragmentShadingRateKHR");
    context->GetPhysicalDeviceFragmentShadingRatesKHR = (PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR) load(userptr, "vkGetPhysicalDeviceFragmentShadingRatesKHR");
}
static void glad_vk_load_VK_KHR_get_display_properties2(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_get_display_properties2) return;
    context->GetDisplayModeProperties2KHR = (PFN_vkGetDisplayModeProperties2KHR) load(userptr, "vkGetDisplayModeProperties2KHR");
    context->GetDisplayPlaneCapabilities2KHR = (PFN_vkGetDisplayPlaneCapabilities2KHR) load(userptr, "vkGetDisplayPlaneCapabilities2KHR");
    context->GetPhysicalDeviceDisplayPlaneProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR) load(userptr, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR");
    context->GetPhysicalDeviceDisplayProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayProperties2KHR) load(userptr, "vkGetPhysicalDeviceDisplayProperties2KHR");
}
static void glad_vk_load_VK_KHR_get_surface_capabilities2(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_get_surface_capabilities2) return;
    context->GetPhysicalDeviceSurfaceCapabilities2KHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR) load(userptr, "vkGetPhysicalDeviceSurfaceCapabilities2KHR");
    context->GetPhysicalDeviceSurfaceFormats2KHR = (PFN_vkGetPhysicalDeviceSurfaceFormats2KHR) load(userptr, "vkGetPhysicalDeviceSurfaceFormats2KHR");
}
static void glad_vk_load_VK_KHR_line_rasterization(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_line_rasterization) return;
    context->CmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR) load(userptr, "vkCmdSetLineStippleKHR");
}
static void glad_vk_load_VK_KHR_object_refresh(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_object_refresh) return;
    context->CmdRefreshObjectsKHR = (PFN_vkCmdRefreshObjectsKHR) load(userptr, "vkCmdRefreshObjectsKHR");
    context->GetPhysicalDeviceRefreshableObjectTypesKHR = (PFN_vkGetPhysicalDeviceRefreshableObjectTypesKHR) load(userptr, "vkGetPhysicalDeviceRefreshableObjectTypesKHR");
}
static void glad_vk_load_VK_KHR_performance_query(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_performance_query) return;
    context->AcquireProfilingLockKHR = (PFN_vkAcquireProfilingLockKHR) load(userptr, "vkAcquireProfilingLockKHR");
    context->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR) load(userptr, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
    context->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = (PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR) load(userptr, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
    context->ReleaseProfilingLockKHR = (PFN_vkReleaseProfilingLockKHR) load(userptr, "vkReleaseProfilingLockKHR");
}
static void glad_vk_load_VK_KHR_shared_presentable_image(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_shared_presentable_image) return;
    context->GetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR) load(userptr, "vkGetSwapchainStatusKHR");
}
static void glad_vk_load_VK_KHR_surface(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_surface) return;
    context->DestroySurfaceKHR = (PFN_vkDestroySurfaceKHR) load(userptr, "vkDestroySurfaceKHR");
    context->GetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) load(userptr, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
    context->GetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR) load(userptr, "vkGetPhysicalDeviceSurfaceFormatsKHR");
    context->GetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR) load(userptr, "vkGetPhysicalDeviceSurfacePresentModesKHR");
    context->GetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR) load(userptr, "vkGetPhysicalDeviceSurfaceSupportKHR");
}
static void glad_vk_load_VK_KHR_swapchain(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_swapchain) return;
    context->AcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR) load(userptr, "vkAcquireNextImage2KHR");
    context->AcquireNextImageKHR = (PFN_vkAcquireNextImageKHR) load(userptr, "vkAcquireNextImageKHR");
    context->CreateSwapchainKHR = (PFN_vkCreateSwapchainKHR) load(userptr, "vkCreateSwapchainKHR");
    context->DestroySwapchainKHR = (PFN_vkDestroySwapchainKHR) load(userptr, "vkDestroySwapchainKHR");
    context->GetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR) load(userptr, "vkGetDeviceGroupPresentCapabilitiesKHR");
    context->GetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR) load(userptr, "vkGetDeviceGroupSurfacePresentModesKHR");
    context->GetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR) load(userptr, "vkGetPhysicalDevicePresentRectanglesKHR");
    context->GetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR) load(userptr, "vkGetSwapchainImagesKHR");
    context->QueuePresentKHR = (PFN_vkQueuePresentKHR) load(userptr, "vkQueuePresentKHR");
}
static void glad_vk_load_VK_KHR_synchronization2(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_synchronization2) return;
    context->CmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR) load(userptr, "vkCmdPipelineBarrier2KHR");
    context->CmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR) load(userptr, "vkCmdResetEvent2KHR");
    context->CmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR) load(userptr, "vkCmdSetEvent2KHR");
    context->CmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR) load(userptr, "vkCmdWaitEvents2KHR");
    context->CmdWriteBufferMarker2AMD = (PFN_vkCmdWriteBufferMarker2AMD) load(userptr, "vkCmdWriteBufferMarker2AMD");
    context->CmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR) load(userptr, "vkCmdWriteTimestamp2KHR");
    context->GetQueueCheckpointData2NV = (PFN_vkGetQueueCheckpointData2NV) load(userptr, "vkGetQueueCheckpointData2NV");
    context->QueueSubmit2KHR = (PFN_vkQueueSubmit2KHR) load(userptr, "vkQueueSubmit2KHR");
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_acquire_winrt_display(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_acquire_winrt_display) return;
    context->AcquireWinrtDisplayNV = (PFN_vkAcquireWinrtDisplayNV) load(userptr, "vkAcquireWinrtDisplayNV");
    context->GetWinrtDisplayNV = (PFN_vkGetWinrtDisplayNV) load(userptr, "vkGetWinrtDisplayNV");
}

#endif
#if defined(VK_USE_PLATFORM_SCI)
static void glad_vk_load_VK_NV_external_memory_sci_buf(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_external_memory_sci_buf) return;
    context->GetMemorySciBufNV = (PFN_vkGetMemorySciBufNV) load(userptr, "vkGetMemorySciBufNV");
    context->GetPhysicalDeviceExternalMemorySciBufPropertiesNV = (PFN_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV) load(userptr, "vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV");
    context->GetPhysicalDeviceSciBufAttributesNV = (PFN_vkGetPhysicalDeviceSciBufAttributesNV) load(userptr, "vkGetPhysicalDeviceSciBufAttributesNV");
}

#endif
#if defined(VK_USE_PLATFORM_SCI)
static void glad_vk_load_VK_NV_external_sci_sync(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_external_sci_sync) return;
    context->GetFenceSciSyncFenceNV = (PFN_vkGetFenceSciSyncFenceNV) load(userptr, "vkGetFenceSciSyncFenceNV");
    context->GetFenceSciSyncObjNV = (PFN_vkGetFenceSciSyncObjNV) load(userptr, "vkGetFenceSciSyncObjNV");
    context->GetPhysicalDeviceSciSyncAttributesNV = (PFN_vkGetPhysicalDeviceSciSyncAttributesNV) load(userptr, "vkGetPhysicalDeviceSciSyncAttributesNV");
    context->GetSemaphoreSciSyncObjNV = (PFN_vkGetSemaphoreSciSyncObjNV) load(userptr, "vkGetSemaphoreSciSyncObjNV");
    context->ImportFenceSciSyncFenceNV = (PFN_vkImportFenceSciSyncFenceNV) load(userptr, "vkImportFenceSciSyncFenceNV");
    context->ImportFenceSciSyncObjNV = (PFN_vkImportFenceSciSyncObjNV) load(userptr, "vkImportFenceSciSyncObjNV");
    context->ImportSemaphoreSciSyncObjNV = (PFN_vkImportSemaphoreSciSyncObjNV) load(userptr, "vkImportSemaphoreSciSyncObjNV");
}

#endif
#if defined(VK_USE_PLATFORM_SCI)
static void glad_vk_load_VK_NV_external_sci_sync2(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_external_sci_sync2) return;
    context->CreateSemaphoreSciSyncPoolNV = (PFN_vkCreateSemaphoreSciSyncPoolNV) load(userptr, "vkCreateSemaphoreSciSyncPoolNV");
    context->DestroySemaphoreSciSyncPoolNV = (PFN_vkDestroySemaphoreSciSyncPoolNV) load(userptr, "vkDestroySemaphoreSciSyncPoolNV");
    context->GetFenceSciSyncFenceNV = (PFN_vkGetFenceSciSyncFenceNV) load(userptr, "vkGetFenceSciSyncFenceNV");
    context->GetFenceSciSyncObjNV = (PFN_vkGetFenceSciSyncObjNV) load(userptr, "vkGetFenceSciSyncObjNV");
    context->GetPhysicalDeviceSciSyncAttributesNV = (PFN_vkGetPhysicalDeviceSciSyncAttributesNV) load(userptr, "vkGetPhysicalDeviceSciSyncAttributesNV");
    context->ImportFenceSciSyncFenceNV = (PFN_vkImportFenceSciSyncFenceNV) load(userptr, "vkImportFenceSciSyncFenceNV");
    context->ImportFenceSciSyncObjNV = (PFN_vkImportFenceSciSyncObjNV) load(userptr, "vkImportFenceSciSyncObjNV");
}

#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_external_memory_screen_buffer(GladVulkanscContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QNX_external_memory_screen_buffer) return;
    context->GetScreenBufferPropertiesQNX = (PFN_vkGetScreenBufferPropertiesQNX) load(userptr, "vkGetScreenBufferPropertiesQNX");
}

#endif



static int glad_vk_get_extensions(GladVulkanscContext *context, VkPhysicalDevice physical_device, uint32_t *out_extension_count, char ***out_extensions) {
    uint32_t i;
    uint32_t instance_extension_count = 0;
    uint32_t device_extension_count = 0;
    uint32_t max_extension_count = 0;
    uint32_t total_extension_count = 0;
    char **extensions = NULL;
    VkExtensionProperties *ext_properties = NULL;
    VkResult result;

    if (context->EnumerateInstanceExtensionProperties == NULL || (physical_device != NULL && context->EnumerateDeviceExtensionProperties == NULL)) {
        return 0;
    }

    result = context->EnumerateInstanceExtensionProperties(NULL, &instance_extension_count, NULL);
    if (result != VK_SUCCESS) {
        return 0;
    }

    if (physical_device != NULL) {
        result = context->EnumerateDeviceExtensionProperties(physical_device, NULL, &device_extension_count, NULL);
        if (result != VK_SUCCESS) {
            return 0;
        }
    }

    total_extension_count = instance_extension_count + device_extension_count;
    if (total_extension_count <= 0) {
        return 0;
    }

    max_extension_count = instance_extension_count > device_extension_count
        ? instance_extension_count : device_extension_count;

    ext_properties = (VkExtensionProperties*) malloc(max_extension_count * sizeof(VkExtensionProperties));
    if (ext_properties == NULL) {
        goto glad_vk_get_extensions_error;
    }

    result = context->EnumerateInstanceExtensionProperties(NULL, &instance_extension_count, ext_properties);
    if (result != VK_SUCCESS) {
        goto glad_vk_get_extensions_error;
    }

    extensions = (char**) calloc(total_extension_count, sizeof(char*));
    if (extensions == NULL) {
        goto glad_vk_get_extensions_error;
    }

    for (i = 0; i < instance_extension_count; ++i) {
        VkExtensionProperties ext = ext_properties[i];

        size_t extension_name_length = strlen(ext.extensionName) + 1;
        extensions[i] = (char*) malloc(extension_name_length * sizeof(char));
        if (extensions[i] == NULL) {
            goto glad_vk_get_extensions_error;
        }
        memcpy(extensions[i], ext.extensionName, extension_name_length * sizeof(char));
    }

    if (physical_device != NULL) {
        result = context->EnumerateDeviceExtensionProperties(physical_device, NULL, &device_extension_count, ext_properties);
        if (result != VK_SUCCESS) {
            goto glad_vk_get_extensions_error;
        }

        for (i = 0; i < device_extension_count; ++i) {
            VkExtensionProperties ext = ext_properties[i];

            size_t extension_name_length = strlen(ext.extensionName) + 1;
            extensions[instance_extension_count + i] = (char*) malloc(extension_name_length * sizeof(char));
            if (extensions[instance_extension_count + i] == NULL) {
                goto glad_vk_get_extensions_error;
            }
            memcpy(extensions[instance_extension_count + i], ext.extensionName, extension_name_length * sizeof(char));
        }
    }

    free((void*) ext_properties);

    *out_extension_count = total_extension_count;
    *out_extensions = extensions;

    return 1;

glad_vk_get_extensions_error:
    free((void*) ext_properties);
    if (extensions != NULL) {
        for (i = 0; i < total_extension_count; ++i) {
            free((void*) extensions[i]);
        }
        free(extensions);
    }
    return 0;
}

static void glad_vk_free_extensions(uint32_t extension_count, char **extensions) {
    uint32_t i;

    for(i = 0; i < extension_count ; ++i) {
        free((void*) (extensions[i]));
    }

    free((void*) extensions);
}

static int glad_vk_has_extension(const char *name, uint32_t extension_count, char **extensions) {
    uint32_t i;

    for (i = 0; i < extension_count; ++i) {
        if(extensions[i] != NULL && strcmp(name, extensions[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

static GLADapiproc glad_vk_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_vk_find_extensions_vulkansc(GladVulkanscContext *context, VkPhysicalDevice physical_device) {
    uint32_t extension_count = 0;
    char **extensions = NULL;
    if (!glad_vk_get_extensions(context, physical_device, &extension_count, &extensions)) return 0;

    context->EXT_4444_formats = glad_vk_has_extension("VK_EXT_4444_formats", extension_count, extensions);
    context->EXT_application_parameters = glad_vk_has_extension("VK_EXT_application_parameters", extension_count, extensions);
    context->EXT_astc_decode_mode = glad_vk_has_extension("VK_EXT_astc_decode_mode", extension_count, extensions);
    context->EXT_blend_operation_advanced = glad_vk_has_extension("VK_EXT_blend_operation_advanced", extension_count, extensions);
    context->EXT_color_write_enable = glad_vk_has_extension("VK_EXT_color_write_enable", extension_count, extensions);
    context->EXT_conservative_rasterization = glad_vk_has_extension("VK_EXT_conservative_rasterization", extension_count, extensions);
    context->EXT_custom_border_color = glad_vk_has_extension("VK_EXT_custom_border_color", extension_count, extensions);
    context->EXT_debug_utils = glad_vk_has_extension("VK_EXT_debug_utils", extension_count, extensions);
    context->EXT_depth_clip_enable = glad_vk_has_extension("VK_EXT_depth_clip_enable", extension_count, extensions);
    context->EXT_depth_range_unrestricted = glad_vk_has_extension("VK_EXT_depth_range_unrestricted", extension_count, extensions);
    context->EXT_direct_mode_display = glad_vk_has_extension("VK_EXT_direct_mode_display", extension_count, extensions);
    context->EXT_discard_rectangles = glad_vk_has_extension("VK_EXT_discard_rectangles", extension_count, extensions);
    context->EXT_display_control = glad_vk_has_extension("VK_EXT_display_control", extension_count, extensions);
    context->EXT_display_surface_counter = glad_vk_has_extension("VK_EXT_display_surface_counter", extension_count, extensions);
    context->EXT_extended_dynamic_state = glad_vk_has_extension("VK_EXT_extended_dynamic_state", extension_count, extensions);
    context->EXT_extended_dynamic_state2 = glad_vk_has_extension("VK_EXT_extended_dynamic_state2", extension_count, extensions);
    context->EXT_external_memory_dma_buf = glad_vk_has_extension("VK_EXT_external_memory_dma_buf", extension_count, extensions);
    context->EXT_external_memory_host = glad_vk_has_extension("VK_EXT_external_memory_host", extension_count, extensions);
    context->EXT_filter_cubic = glad_vk_has_extension("VK_EXT_filter_cubic", extension_count, extensions);
    context->EXT_fragment_shader_interlock = glad_vk_has_extension("VK_EXT_fragment_shader_interlock", extension_count, extensions);
    context->EXT_hdr_metadata = glad_vk_has_extension("VK_EXT_hdr_metadata", extension_count, extensions);
    context->EXT_headless_surface = glad_vk_has_extension("VK_EXT_headless_surface", extension_count, extensions);
    context->EXT_image_drm_format_modifier = glad_vk_has_extension("VK_EXT_image_drm_format_modifier", extension_count, extensions);
    context->EXT_image_robustness = glad_vk_has_extension("VK_EXT_image_robustness", extension_count, extensions);
    context->EXT_index_type_uint8 = glad_vk_has_extension("VK_EXT_index_type_uint8", extension_count, extensions);
    context->EXT_line_rasterization = glad_vk_has_extension("VK_EXT_line_rasterization", extension_count, extensions);
    context->EXT_memory_budget = glad_vk_has_extension("VK_EXT_memory_budget", extension_count, extensions);
    context->EXT_pci_bus_info = glad_vk_has_extension("VK_EXT_pci_bus_info", extension_count, extensions);
    context->EXT_post_depth_coverage = glad_vk_has_extension("VK_EXT_post_depth_coverage", extension_count, extensions);
    context->EXT_queue_family_foreign = glad_vk_has_extension("VK_EXT_queue_family_foreign", extension_count, extensions);
    context->EXT_robustness2 = glad_vk_has_extension("VK_EXT_robustness2", extension_count, extensions);
    context->EXT_sample_locations = glad_vk_has_extension("VK_EXT_sample_locations", extension_count, extensions);
    context->EXT_shader_atomic_float = glad_vk_has_extension("VK_EXT_shader_atomic_float", extension_count, extensions);
    context->EXT_shader_demote_to_helper_invocation = glad_vk_has_extension("VK_EXT_shader_demote_to_helper_invocation", extension_count, extensions);
    context->EXT_shader_image_atomic_int64 = glad_vk_has_extension("VK_EXT_shader_image_atomic_int64", extension_count, extensions);
    context->EXT_shader_stencil_export = glad_vk_has_extension("VK_EXT_shader_stencil_export", extension_count, extensions);
    context->EXT_subgroup_size_control = glad_vk_has_extension("VK_EXT_subgroup_size_control", extension_count, extensions);
    context->EXT_swapchain_colorspace = glad_vk_has_extension("VK_EXT_swapchain_colorspace", extension_count, extensions);
    context->EXT_texel_buffer_alignment = glad_vk_has_extension("VK_EXT_texel_buffer_alignment", extension_count, extensions);
    context->EXT_texture_compression_astc_hdr = glad_vk_has_extension("VK_EXT_texture_compression_astc_hdr", extension_count, extensions);
    context->EXT_validation_features = glad_vk_has_extension("VK_EXT_validation_features", extension_count, extensions);
    context->EXT_vertex_input_dynamic_state = glad_vk_has_extension("VK_EXT_vertex_input_dynamic_state", extension_count, extensions);
    context->EXT_ycbcr_2plane_444_formats = glad_vk_has_extension("VK_EXT_ycbcr_2plane_444_formats", extension_count, extensions);
    context->EXT_ycbcr_image_arrays = glad_vk_has_extension("VK_EXT_ycbcr_image_arrays", extension_count, extensions);
    context->KHR_calibrated_timestamps = glad_vk_has_extension("VK_KHR_calibrated_timestamps", extension_count, extensions);
    context->KHR_copy_commands2 = glad_vk_has_extension("VK_KHR_copy_commands2", extension_count, extensions);
    context->KHR_display = glad_vk_has_extension("VK_KHR_display", extension_count, extensions);
    context->KHR_display_swapchain = glad_vk_has_extension("VK_KHR_display_swapchain", extension_count, extensions);
    context->KHR_external_fence_fd = glad_vk_has_extension("VK_KHR_external_fence_fd", extension_count, extensions);
    context->KHR_external_memory_fd = glad_vk_has_extension("VK_KHR_external_memory_fd", extension_count, extensions);
    context->KHR_external_semaphore_fd = glad_vk_has_extension("VK_KHR_external_semaphore_fd", extension_count, extensions);
    context->KHR_fragment_shading_rate = glad_vk_has_extension("VK_KHR_fragment_shading_rate", extension_count, extensions);
    context->KHR_get_display_properties2 = glad_vk_has_extension("VK_KHR_get_display_properties2", extension_count, extensions);
    context->KHR_get_surface_capabilities2 = glad_vk_has_extension("VK_KHR_get_surface_capabilities2", extension_count, extensions);
    context->KHR_global_priority = glad_vk_has_extension("VK_KHR_global_priority", extension_count, extensions);
    context->KHR_incremental_present = glad_vk_has_extension("VK_KHR_incremental_present", extension_count, extensions);
    context->KHR_index_type_uint8 = glad_vk_has_extension("VK_KHR_index_type_uint8", extension_count, extensions);
    context->KHR_line_rasterization = glad_vk_has_extension("VK_KHR_line_rasterization", extension_count, extensions);
    context->KHR_object_refresh = glad_vk_has_extension("VK_KHR_object_refresh", extension_count, extensions);
    context->KHR_performance_query = glad_vk_has_extension("VK_KHR_performance_query", extension_count, extensions);
    context->KHR_shader_clock = glad_vk_has_extension("VK_KHR_shader_clock", extension_count, extensions);
    context->KHR_shader_terminate_invocation = glad_vk_has_extension("VK_KHR_shader_terminate_invocation", extension_count, extensions);
    context->KHR_shared_presentable_image = glad_vk_has_extension("VK_KHR_shared_presentable_image", extension_count, extensions);
    context->KHR_surface = glad_vk_has_extension("VK_KHR_surface", extension_count, extensions);
    context->KHR_swapchain = glad_vk_has_extension("VK_KHR_swapchain", extension_count, extensions);
    context->KHR_swapchain_mutable_format = glad_vk_has_extension("VK_KHR_swapchain_mutable_format", extension_count, extensions);
    context->KHR_synchronization2 = glad_vk_has_extension("VK_KHR_synchronization2", extension_count, extensions);
    context->KHR_vertex_attribute_divisor = glad_vk_has_extension("VK_KHR_vertex_attribute_divisor", extension_count, extensions);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    context->NV_acquire_winrt_display = glad_vk_has_extension("VK_NV_acquire_winrt_display", extension_count, extensions);

#endif
#if defined(VK_USE_PLATFORM_SCI)
    context->NV_external_memory_sci_buf = glad_vk_has_extension("VK_NV_external_memory_sci_buf", extension_count, extensions);

#endif
#if defined(VK_USE_PLATFORM_SCI)
    context->NV_external_sci_sync = glad_vk_has_extension("VK_NV_external_sci_sync", extension_count, extensions);

#endif
#if defined(VK_USE_PLATFORM_SCI)
    context->NV_external_sci_sync2 = glad_vk_has_extension("VK_NV_external_sci_sync2", extension_count, extensions);

#endif
    context->NV_private_vendor_info = glad_vk_has_extension("VK_NV_private_vendor_info", extension_count, extensions);
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    context->QNX_external_memory_screen_buffer = glad_vk_has_extension("VK_QNX_external_memory_screen_buffer", extension_count, extensions);

#endif

    GLAD_UNUSED(glad_vk_has_extension);

    glad_vk_free_extensions(extension_count, extensions);

    return 1;
}

static int glad_vk_find_core_vulkansc(GladVulkanscContext *context, VkPhysicalDevice physical_device) {
    int major = 1;
    int minor = 0;

#ifdef VK_VERSION_1_1
    if (context->EnumerateInstanceVersion != NULL) {
        uint32_t version;
        VkResult result;

        result = context->EnumerateInstanceVersion(&version);
        if (result == VK_SUCCESS) {
            major = (int) VK_VERSION_MAJOR(version);
            minor = (int) VK_VERSION_MINOR(version);
        }
    }
#endif

    if (physical_device != NULL && context->GetPhysicalDeviceProperties != NULL) {
        VkPhysicalDeviceProperties properties;
        context->GetPhysicalDeviceProperties(physical_device, &properties);

        major = (int) VK_VERSION_MAJOR(properties.apiVersion);
        minor = (int) VK_VERSION_MINOR(properties.apiVersion);
    }

    context->SC_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    context->VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
    context->VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
    context->VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;

    return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadVulkanscContextUserPtr(GladVulkanscContext *context, VkPhysicalDevice physical_device, GLADuserptrloadfunc load, void *userptr) {
    int version;

#ifdef VK_VERSION_1_1
    context->EnumerateInstanceVersion  = (PFN_vkEnumerateInstanceVersion) load(userptr, "vkEnumerateInstanceVersion");
#endif
    version = glad_vk_find_core_vulkansc(context, physical_device);
    if (!version) {
        return 0;
    }

    glad_vk_load_VKSC_VERSION_1_0(context, load, userptr);
    glad_vk_load_VK_VERSION_1_1(context, load, userptr);
    glad_vk_load_VK_VERSION_1_2(context, load, userptr);
    glad_vk_load_VK_VERSION_1_3(context, load, userptr);

    if (!glad_vk_find_extensions_vulkansc(context, physical_device)) return 0;
    glad_vk_load_VK_EXT_color_write_enable(context, load, userptr);
    glad_vk_load_VK_EXT_debug_utils(context, load, userptr);
    glad_vk_load_VK_EXT_direct_mode_display(context, load, userptr);
    glad_vk_load_VK_EXT_discard_rectangles(context, load, userptr);
    glad_vk_load_VK_EXT_display_control(context, load, userptr);
    glad_vk_load_VK_EXT_display_surface_counter(context, load, userptr);
    glad_vk_load_VK_EXT_extended_dynamic_state(context, load, userptr);
    glad_vk_load_VK_EXT_extended_dynamic_state2(context, load, userptr);
    glad_vk_load_VK_EXT_external_memory_host(context, load, userptr);
    glad_vk_load_VK_EXT_hdr_metadata(context, load, userptr);
    glad_vk_load_VK_EXT_headless_surface(context, load, userptr);
    glad_vk_load_VK_EXT_image_drm_format_modifier(context, load, userptr);
    glad_vk_load_VK_EXT_line_rasterization(context, load, userptr);
    glad_vk_load_VK_EXT_sample_locations(context, load, userptr);
    glad_vk_load_VK_EXT_vertex_input_dynamic_state(context, load, userptr);
    glad_vk_load_VK_KHR_calibrated_timestamps(context, load, userptr);
    glad_vk_load_VK_KHR_copy_commands2(context, load, userptr);
    glad_vk_load_VK_KHR_display(context, load, userptr);
    glad_vk_load_VK_KHR_display_swapchain(context, load, userptr);
    glad_vk_load_VK_KHR_external_fence_fd(context, load, userptr);
    glad_vk_load_VK_KHR_external_memory_fd(context, load, userptr);
    glad_vk_load_VK_KHR_external_semaphore_fd(context, load, userptr);
    glad_vk_load_VK_KHR_fragment_shading_rate(context, load, userptr);
    glad_vk_load_VK_KHR_get_display_properties2(context, load, userptr);
    glad_vk_load_VK_KHR_get_surface_capabilities2(context, load, userptr);
    glad_vk_load_VK_KHR_line_rasterization(context, load, userptr);
    glad_vk_load_VK_KHR_object_refresh(context, load, userptr);
    glad_vk_load_VK_KHR_performance_query(context, load, userptr);
    glad_vk_load_VK_KHR_shared_presentable_image(context, load, userptr);
    glad_vk_load_VK_KHR_surface(context, load, userptr);
    glad_vk_load_VK_KHR_swapchain(context, load, userptr);
    glad_vk_load_VK_KHR_synchronization2(context, load, userptr);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    glad_vk_load_VK_NV_acquire_winrt_display(context, load, userptr);

#endif
#if defined(VK_USE_PLATFORM_SCI)
    glad_vk_load_VK_NV_external_memory_sci_buf(context, load, userptr);

#endif
#if defined(VK_USE_PLATFORM_SCI)
    glad_vk_load_VK_NV_external_sci_sync(context, load, userptr);

#endif
#if defined(VK_USE_PLATFORM_SCI)
    glad_vk_load_VK_NV_external_sci_sync2(context, load, userptr);

#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    glad_vk_load_VK_QNX_external_memory_screen_buffer(context, load, userptr);

#endif


    return version;
}


int gladLoadVulkanscContext(GladVulkanscContext *context, VkPhysicalDevice physical_device, GLADloadfunc load) {
    return gladLoadVulkanscContextUserPtr(context, physical_device, glad_vk_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}



 


#ifdef __cplusplus
}
#endif
