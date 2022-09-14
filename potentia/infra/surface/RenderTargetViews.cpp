#include "RenderTargetViews.h"
#include "infra/devices/LogicalDevice.h"
#include "SwapChain.h"
void RenderTargetViews::Create() {
  D3D12_DESCRIPTOR_HEAP_DESC desc = {};
  desc.NumDescriptors = Sync::c_frameCount;
  desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
  ThrowOnFail(LogicalDevice::Get()->GetDevice()->CreateDescriptorHeap(
        &desc, IID_PPV_ARGS(&m_rtvHeap)));
  m_descriptorSize =
      LogicalDevice::Get()->GetDevice()->GetDescriptorHandleIncrementSize(
          D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
      m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

  for (UINT n = 0; n < Sync::c_frameCount; n++) {
    ThrowOnFail(SwapChain::Get()->GetSwapChain()->GetBuffer(
        n, IID_PPV_ARGS(&m_renderTargets[n])));
    LogicalDevice::Get()->GetDevice()->CreateRenderTargetView(
        m_renderTargets[n].Get(), nullptr, rtvHandle);
    rtvHandle.Offset(1, m_descriptorSize);
  }
}
