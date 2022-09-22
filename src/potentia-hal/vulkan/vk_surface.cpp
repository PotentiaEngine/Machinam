#include "vk_surface.h"
#include "glm/common.hpp"
#include "potentia-core/error.h"
#include "potentia-hal/hal_factory.h"
#include "potentia-hal/vulkan/vk_device.h"
#include "potentia-hal/vulkan/vk_window.h"
#include <GLFW/glfw3.h>
#include <cassert>
#include <glm/glm.hpp>
#include <limits>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>
void vk_surface::initialize() {
  VkSurfaceKHR surface;

  auto wind = hal_factory::instance()->get_window();
  auto vkWindow = reinterpret_cast<vk_window *>(wind.get());

  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());

  glfwCreateWindowSurface(static_cast<VkInstance>(vkDevice->get_instance()),
                          vkWindow->get_window(), nullptr, &surface);
  m_surface = vk::SurfaceKHR(surface);

  auto formats = vkDevice->get_physical().getSurfaceFormatsKHR(m_surface);
  assert(formats.empty());

  vk::Format format = (formats[0].format == vk::Format::eUndefined)
                          ? vk::Format::eB8G8R8A8Unorm
                          : formats[0].format;
  auto surfaceCaps =
      vkDevice->get_physical().getSurfaceCapabilitiesKHR(m_surface);

  vk::Extent2D swapChainExtent;

  if (surfaceCaps.currentExtent.width == std::numeric_limits<uint32_t>::max()) {
    swapChainExtent.width =
        glm::clamp(vkWindow->get_size().width, surfaceCaps.minImageExtent.width,
                   surfaceCaps.maxImageExtent.width);
    swapChainExtent.height = glm::clamp(vkWindow->get_size().height,
                                        surfaceCaps.minImageExtent.height,
                                        surfaceCaps.maxImageExtent.height);
  } else {
    swapChainExtent = surfaceCaps.currentExtent;
  }

  auto swapChainPresentMode = vk::PresentModeKHR::eFifo;

  auto preTransform = (surfaceCaps.supportedTransforms &
                       vk::SurfaceTransformFlagBitsKHR::eIdentity)
                          ? vk::SurfaceTransformFlagBitsKHR::eIdentity
                          : surfaceCaps.currentTransform;
  vk::CompositeAlphaFlagBitsKHR compositeAlpha =
      (surfaceCaps.supportedCompositeAlpha &
       vk::CompositeAlphaFlagBitsKHR::ePreMultiplied)
          ? vk::CompositeAlphaFlagBitsKHR::ePreMultiplied
      : (surfaceCaps.supportedCompositeAlpha &
         vk::CompositeAlphaFlagBitsKHR::ePostMultiplied)
          ? vk::CompositeAlphaFlagBitsKHR::ePostMultiplied
      : (surfaceCaps.supportedCompositeAlpha &
         vk::CompositeAlphaFlagBitsKHR::eInherit)
          ? vk::CompositeAlphaFlagBitsKHR::eInherit
          : vk::CompositeAlphaFlagBitsKHR::eOpaque;

  vk::SwapchainCreateInfoKHR swapChainCreateInfo(
      vk::SwapchainCreateFlagsKHR(), m_surface, surfaceCaps.minImageCount,
      format, vk::ColorSpaceKHR::eSrgbNonlinear, swapChainExtent, 1,
      vk::ImageUsageFlagBits::eColorAttachment, vk::SharingMode::eExclusive, {},
      preTransform, compositeAlpha, swapChainPresentMode, true, nullptr);

  uint32_t queueFamilyIndices[2] = {vkDevice->get_graphics_qfi(),
                                    vkDevice->get_present_qfi()};

  if (vkDevice->get_graphics_qfi() != vkDevice->get_present_qfi()) {
    swapChainCreateInfo.imageSharingMode = vk::SharingMode::eConcurrent;
    swapChainCreateInfo.queueFamilyIndexCount = 2;
    swapChainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
  }

  m_swapChain = vkDevice->get_device().createSwapchainKHR(swapChainCreateInfo);

  std::vector<vk::Image> swapChainImages =
      vkDevice->get_device().getSwapchainImagesKHR(m_swapChain);

  std::vector<vk::ImageView> imageViews;
  imageViews.reserve(swapChainImages.size());
  vk::ImageViewCreateInfo imageViewCreateInfo(
      {}, {}, vk::ImageViewType::e2D, format, {},
      {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
  for (auto image : swapChainImages) {
    imageViewCreateInfo.image = image;
    imageViews.push_back(
        vkDevice->get_device().createImageView(imageViewCreateInfo));
  }
  m_images = swapChainImages;
  m_imageViews = imageViews;
}

void vk_surface::init_depth_buffer() {
  const vk::Format format = vk::Format::eD16Unorm;
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());

  vk::FormatProperties formatProps =
      vkDevice->get_physical()->getFormatProperties(format);

  vk::ImageTiling tiling;
  if (formatProps.linearTilingFeatures &
      vk::FormatFeatureFlagBits::eDepthStencilAttachment) {
    tiling = vk::ImageTiling::eLinear;
  } else if (formatProps.optimalTilingFeatures &
             vk::FormatFeatureFlagBits::eDepthStencilAttachment) {
    tiling = vk::ImageTiling::eOptimal;
  }
  else {
    THROW_P000003;
  }
  auto wind = hal_factory::instance()->get_window();
  auto vkWindow = reinterpret_cast<vk_window *>(wind.get());

  vk::ImageCreateInfo imageCreateInfo(vk::ImageCreateFlags(), vk::ImageType::e2D, format, vk::Extent3D(vkWindow->get_size(), 1), 1, 1, vk::SampleCountFlagBits::e1, tiling, vk::ImageUsageFlagBits::eDepthStencilAttachment);

  m_depthImage = vkDevice->get_device().createImage(imageCreateInfo);
  
  vk::PhysicalDeviceMemoryProperties memoryProps = vkDevice->get_physical().getMemoryProperties();
  vk::MemoryRequirements memoryReqs = vkDevice->get_device().getImageMemoryRequirements(m_depthImage);

  uint32_t typeBits = memoryReqs.memoryTypeBits;
  uint32_t typeIndex = ~0;

  for (uint32_t i = 0; i< memoryProps.memoryTypeCount; i++){
          if ( ( typeBits & 1 ) &&
           ( ( memoryProps.memoryTypes[i].propertyFlags & vk::MemoryPropertyFlagBits::eDeviceLocal ) == vk::MemoryPropertyFlagBits::eDeviceLocal ) )
      {
        typeIndex = i;
        break;
      }
      typeBits >>= 1;
  }
  assert(typeIndex != ~0);
  vk::DeviceMemory depthMemory = vkDevice->get_device().allocateMemory(vk::MemoryAllocateInfo(memoryReqs.size, typeIndex));

  vkDevice->get_device().bindImageMemory(m_depthImage, depthMemory, 0);

  m_depthView = vkDevice->get_device().createImageView(vk::ImageViewCreateInfo(vk::ImageViewCreateFlags(), m_depthImage, vk::ImageViewType::e2D, format, {}, {vk::ImageAspectFlagBits::eDepth, 0, 1, 0, 1}));

}

void vk_surface::destroy() {
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());
  
  auto dev = vkDevice->get_device();
  dev.destroyImageView(m_depthView);
  dev.freeMemory(m_depthMemory);
  dev.destroyImage(m_depthImage);

  for (auto imgV : m_imageViews) {
    dev.destroyImageView(imgV);
  }

  dev.destroySwapchainKHR(m_swapChain);
  vkDevice->get_instance().destroySurfaceKHR(m_surface);
}
