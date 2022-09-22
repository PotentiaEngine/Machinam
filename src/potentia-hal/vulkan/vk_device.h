#pragma once

#include <potentia-core/pch.h>
#include <potentia-hal/interface/device.h>
#include <vulkan/vulkan_handles.hpp>

class vk_device : public device {
  public:
    void initialize() override;
    void destroy() override;
    void init_physical() override;
    vk::Device get_device() const {return m_device;};
    vk::Instance get_instance() const { return m_instance; }
    vk::PhysicalDevice get_physical() const { return m_physicalDevice; };
    uint32_t get_graphics_qfi() const { return m_graphicsQueueFamilyIndex; };
    uint32_t get_present_qfi() const {return m_presentQueueFamilyIndex; };
  protected:
    uint32_t find_graphics_queue_index(std::vector<vk::QueueFamilyProperties>);
    uint32_t find_surface_queue_index(std::vector<vk::QueueFamilyProperties>, uint32_t*);
    void init_logical_device();
    vk::Instance m_instance;
    vk::PhysicalDevice m_physicalDevice;\
    vk::Device m_device;
    uint32_t m_graphicsQueueFamilyIndex;
    uint32_t m_presentQueueFamilyIndex;
#if !defined(NDEBUG)
    vk::DebugUtilsMessengerEXT m_debugMessenger;
#endif
};
