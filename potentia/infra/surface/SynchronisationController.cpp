#include "SynchronisationController.h"
#include "core/EngineCore.h"
#include "infra/command/CommandQueue.h"
#include "infra/devices/LogicalDevice.h"
#include "infra/surface/SwapChain.h"
#include <errhandlingapi.h>
#include <synchapi.h>
#include <winerror.h>

void SynchronisationController::Create() {
  ThrowOnFail(LogicalDevice::Get()->GetDevice()->CreateFence(
      0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));

  m_fenceValue = 1;
  m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
  if (m_fenceEvent == nullptr) {
    ThrowOnFail(HRESULT_FROM_WIN32(GetLastError()));
  }
}

void SynchronisationController::WaitForGPU() {
  const UINT64 fence = m_fenceValue;
  ThrowOnFail(CommandQueue::Get()->GetCommandQueue()->Signal(m_fence.Get(), fence));
  m_fenceValue ++;

    ThrowOnFail(m_fence->SetEventOnCompletion(fence, m_fenceEvent));
    WaitForSingleObject(m_fenceEvent, INFINITE);
  m_frameIndex = SwapChain::Get()->GetSwapChain()->GetCurrentBackBufferIndex();
}
