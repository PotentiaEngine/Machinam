#pragma once

#include "core/EngineCore.h"
#include "core/base/Singleton.h"

class HardwareAdapterFactory : public Singleton<HardwareAdapterFactory> {
public:
  void GetHardwareAdapter(IDXGIFactory1* pFactory, IDXGIAdapter1** ppAdapter, bool requestHighPerformanceAdapter);
Getter(ComP(IDXGIFactory6), Factory, m_factory);   
protected:
  ComP(IDXGIFactory6) m_factory;
};
