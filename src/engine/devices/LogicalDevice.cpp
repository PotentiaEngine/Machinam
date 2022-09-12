#include "LogicalDevice.h"
#include "HardwareAdapterFactory.h"
#include "utils.h"
#include <combaseapi.h>
#include <d3d12.h>
#include <dxgi.h>
_Use_decl_annotations_
void LogicalDevice::Create() {

  cptr(dxgi(Factory4)) factory;
  ThrowOnFail(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory)));

  cptr(dxgi(Adapter)) hardwareAdapter;
  ThrowOnFail(factory->EnumWarpAdapter(IID_PPV_ARGS(&hardwareAdapter)));

  ThrowOnFail(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device)));
} 
