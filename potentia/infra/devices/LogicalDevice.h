#pragma once
#include "core/EngineCore.h"
#include "core/base/Singleton.h"


class LogicalDevice : public Singleton<LogicalDevice> {
public:
  void Create();
  Getter(ComP(ID3D12Device), Device, m_device);
private:
  ComP(ID3D12Device) m_device;
};

