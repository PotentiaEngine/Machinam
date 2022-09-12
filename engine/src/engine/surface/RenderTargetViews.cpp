#include "RenderTargetViews.h"

#include <combaseapi.h>
#include <d3d12.h>

#include "d3dx12.h"
#include "engine/devices/LogicalDevice.h"
#include "engine/surface/SwapChain.h"
#include "engine/surface/SynchronisationController.h"
#include "utils.h"

void RenderTargetViews::Create() {
  D3D12_DESCRIPTOR_HEAP_DESC desc = {};
  desc.NumDescriptors = Sync::c_frameCount;
  desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
  ThrowOnFail(LogicalDevice::Instance()->GetDevice()->CreateDescriptorHeap(
      &desc, IID_PPV_ARGS(&m_rtvHeap)));
  m_descriptorSize =
      LogicalDevice::Instance()->GetDevice()->GetDescriptorHandleIncrementSize(
          D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
      m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

  for (UINT n = 0; n < Sync::c_frameCount; n++) {
    ThrowOnFail(SwapChain::Instance()->GetSwapChain()->GetBuffer(
        n, IID_PPV_ARGS(&m_renderTargets[n])));
    LogicalDevice::Instance()->GetDevice()->CreateRenderTargetView(
        m_renderTargets[n].Get(), nullptr, rtvHandle);
    rtvHandle.Offset(1, m_descriptorSize);
  }
}
