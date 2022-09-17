#include "LogicalDevice.h"
#include "HardwareAdapterFactory.h"
#include <dxgi.h>

void LogicalDevice::Create() {

  ComP(IDXGIFactory4) factory;
  ThrowOnFail(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));

  ComP(IDXGIAdapter1) hardwareAdapter;
  HardwareAdapterFactory::Get()->GetHardwareAdapter(factory.Get(), &hardwareAdapter, false);
  //  ThrowOnFail(factory->EnumWarpAdapter(IID_PPV_ARGS(&hardwareAdapter)));

  ThrowOnFail(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device)));
} 
