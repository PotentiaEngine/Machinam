#pragma once

#include "potentia-hal/interface/surface.h"
#include <potentia-core/pch.h>
#include <vulkan/vulkan_handles.hpp>

class vk_surface : public surface {
public:
  void initialize() override;
  vk::SurfaceKHR get_surface() const { return m_surface; };
  void destroy() override;

protected:
  void init_depth_buffer();
  vk::SurfaceKHR m_surface;
  vk::SwapchainKHR m_swapChain;
  std::vector<vk::Image> m_images;
  std::vector<vk::ImageView> m_imageViews;
  vk::Image m_depthImage;
  vk::DeviceMemory m_depthMemory;
  vk::ImageView m_depthView;
};
