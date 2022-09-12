#pragma once

#include "engine/base/Singleton.h"
#include "pch.h"

class HardwareAdapterFactory : public Singleton<HardwareAdapterFactory> {
public:
  void GetHardwareAdapter(dxgi(Factory1)* pFactory, dxgi(Adapter1)** ppAdapter, bool requestHighPerformanceAdapter);
Getter(cptr(dxgi(Factory6)), Factory, m_factory);   
protected:
  cptr(dxgi(Factory6)) m_factory;
};
