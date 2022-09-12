#include "HardwareAdapterFactory.h"

#include <combaseapi.h>
#include <d3d12.h>
#include <d3dcommon.h>
#include <dxgi.h>
#include <dxgi1_6.h>
#include <intsafe.h>
_Use_decl_annotations_
void HardwareAdapterFactory::GetHardwareAdapter(
    dxgi(Factory1) * pFactory, dxgi(Adapter1) * *ppAdapter,
    bool requestHighPerformanceAdapter) {
  *ppAdapter = nullptr;

  cptr(dxgi(Adapter1)) adapter;

  if (SUCCEEDED(pFactory->QueryInterface(IID_PPV_ARGS(&m_factory)))) {
    for (UINT adapterIndex = 0; SUCCEEDED(m_factory->EnumAdapterByGpuPreference(
             adapterIndex,
             requestHighPerformanceAdapter == true
                 ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE
                 : DXGI_GPU_PREFERENCE_UNSPECIFIED,
             IID_PPV_ARGS(&adapter)));
         ++adapterIndex) {
      DXGI_ADAPTER_DESC1 desc;
      adapter->GetDesc1(&desc);
      if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
        continue;
      }

      if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0,
                                      _uuidof(d3d(Device)), nullptr))) {
        break;
      }
    }
  }

  if (adapter.Get() == nullptr) {
    for (UINT adapterIndex = 0; SUCCEEDED(pFactory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex) {
      DXGI_ADAPTER_DESC1 desc;
      adapter->GetDesc1(&desc);

      if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
        continue;
      }

      if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0,
                                      _uuidof(d3d(Device)), nullptr))) {

        break;
      }
    }
  }
  *ppAdapter = adapter.Get();
}
