#include "vk_device.h"

#include "potentia-core/config/config_strings.h"
#include "potentia-core/error.h"
#include "potentia-hal/hal_factory.h"
#include "potentia-hal/vulkan/vk_surface.h"
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <potentia-core/pch.h>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>

VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageTypes,
    VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData, void *) {
#if !defined(NDEBUG)
  if (pCallbackData->messageIdNumber == 648835635) {
    // UNASSIGNED-khronos-Validation-debug-build-warning-message
    return VK_FALSE;
  }
  if (pCallbackData->messageIdNumber == 767975156) {
    // UNASSIGNED-BestPractices-vkCreateInstance-specialuse-extension
    return VK_FALSE;
  }
#endif

  std::cerr << vk::to_string(
                   static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(
                       messageSeverity))
            << ": "
            << vk::to_string(
                   static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(messageTypes))
            << ":\n";
  std::cerr << std::string("\t") << "messageIDName   = <"
            << pCallbackData->pMessageIdName << ">\n";
  std::cerr << std::string("\t")
            << "messageIdNumber = " << pCallbackData->messageIdNumber << "\n";
  std::cerr << std::string("\t") << "message         = <"
            << pCallbackData->pMessage << ">\n";
  if (0 < pCallbackData->queueLabelCount) {
    std::cerr << std::string("\t") << "Queue Labels:\n";
    for (uint32_t i = 0; i < pCallbackData->queueLabelCount; i++) {
      std::cerr << std::string("\t\t") << "labelName = <"
                << pCallbackData->pQueueLabels[i].pLabelName << ">\n";
    }
  }
  if (0 < pCallbackData->cmdBufLabelCount) {
    std::cerr << std::string("\t") << "CommandBuffer Labels:\n";
    for (uint32_t i = 0; i < pCallbackData->cmdBufLabelCount; i++) {
      std::cerr << std::string("\t\t") << "labelName = <"
                << pCallbackData->pCmdBufLabels[i].pLabelName << ">\n";
    }
  }
  if (0 < pCallbackData->objectCount) {
    std::cerr << std::string("\t") << "Objects:\n";
    for (uint32_t i = 0; i < pCallbackData->objectCount; i++) {
      std::cerr << std::string("\t\t") << "Object " << i << "\n";
      std::cerr << std::string("\t\t\t") << "objectType   = "
                << vk::to_string(static_cast<vk::ObjectType>(
                       pCallbackData->pObjects[i].objectType))
                << "\n";
      std::cerr << std::string("\t\t\t")
                << "objectHandle = " << pCallbackData->pObjects[i].objectHandle
                << "\n";
      if (pCallbackData->pObjects[i].pObjectName) {
        std::cerr << std::string("\t\t\t") << "objectName   = <"
                  << pCallbackData->pObjects[i].pObjectName << ">\n";
      }
    }
  }
  return VK_TRUE;
}

void vk_device::initialize() { init_logical_device(); }

void vk_device::destroy() {
  m_device.destroy();

#if !defined(NDEBUG)
  m_instance.destroyDebugUtilsMessengerEXT(m_debugMessenger);
#endif
  m_instance.destroy();
}

void vk_device::init_logical_device() {
  std::vector<vk::QueueFamilyProperties> queueFamilyProperties =
      m_physicalDevice.getQueueFamilyProperties();

    m_graphicsQueueFamilyIndex = find_graphics_queue_index(queueFamilyProperties);
    m_presentQueueFamilyIndex = find_surface_queue_index(queueFamilyProperties, &m_graphicsQueueFamilyIndex);

  float queuePriority = 0.0f;
  vk::DeviceQueueCreateInfo deviceQueueCreateInfo(
      vk::DeviceQueueCreateFlags(), m_graphicsQueueFamilyIndex,
      1, &queuePriority);
  m_device = m_physicalDevice.createDevice(
      vk::DeviceCreateInfo(vk::DeviceCreateFlags(), deviceQueueCreateInfo));
}

void vk_device::init_physical() {

  vk::ApplicationInfo app_info(
      config_strings::instance()->get_value(game_name).c_str(), 1, "Potentia",
      VK_API_VERSION_1_3);
  vk::InstanceCreateInfo create_info({}, &app_info);
  m_instance = vk::createInstance(create_info);
#if !defined(NDEBUG)
  m_debugMessenger = m_instance.createDebugUtilsMessengerEXT(
      {{},
       vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
           vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
       vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
           vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
           vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
       &debugUtilsMessengerCallback});
#endif

  m_physicalDevice = m_instance.enumeratePhysicalDevices().front();
}

uint32_t vk_device::find_graphics_queue_index(
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties) {
  auto propertyIterator =
      std::find_if(queueFamilyProperties.begin(), queueFamilyProperties.end(),
                   [](vk::QueueFamilyProperties const &qfp) {
                     return qfp.queueFlags & vk::QueueFlagBits::eGraphics;
                   });
  size_t graphicsQueueFamilyIndex =
      std::distance(queueFamilyProperties.begin(), propertyIterator);
  assert(graphicsQueueFamilyIndex < queueFamilyProperties.size());
  return graphicsQueueFamilyIndex;
}

uint32_t vk_device::find_surface_queue_index(
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties,
    uint32_t *gfxFamilyIndex) {
  auto surface = hal_factory::instance()->get_surface();
  auto vkSurface = reinterpret_cast<vk_surface *>(surface.get());
  uint32_t presentQueueFamilyIndex =
      m_physicalDevice.getSurfaceSupportKHR(*gfxFamilyIndex,
                                            vkSurface->get_surface())
          ? *gfxFamilyIndex
          : queueFamilyProperties.size();

  if (presentQueueFamilyIndex == queueFamilyProperties.size()) {
    for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
      if ((queueFamilyProperties[i].queueFlags &
           vk::QueueFlagBits::eGraphics) &&
          m_physicalDevice.getSurfaceSupportKHR(i, vkSurface->get_surface())) {
        *gfxFamilyIndex = i;
        presentQueueFamilyIndex = i;
        break;
      }
    }
    if (presentQueueFamilyIndex == queueFamilyProperties.size()) {
      for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
        if (m_physicalDevice.getSurfaceSupportKHR(i,
                                                  vkSurface->get_surface())) {
          presentQueueFamilyIndex = i;
          break;
        }
      }
    }
  }
  if (presentQueueFamilyIndex == queueFamilyProperties.size() || *gfxFamilyIndex == queueFamilyProperties.size()){
      THROW_P000002;
  }
  return presentQueueFamilyIndex;
}
