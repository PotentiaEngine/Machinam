#pragma once

#include "pch.h"
#include "engine/base/Singleton.h"


class LogicalDevice : public Singleton<LogicalDevice> {
public:
  void Create();
  Getter(cptr(d3d(Device)), Device, m_device);
private:
  cptr(d3d(Device)) m_device;
};

