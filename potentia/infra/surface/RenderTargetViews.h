#pragma once

#include "core/base/Singleton.h"
#include "SynchronisationController.h"

class RenderTargetViews : public Singleton<RenderTargetViews> {
 public:
  void Create();
  ComP(ID3D12Resource) GetRTV(UINT frameIndex) const {
    return m_renderTargets[frameIndex];
  } 
 protected:
  ComP(ID3D12Resource) m_renderTargets[SynchronisationController::c_frameCount];
  ComP(ID3D12DescriptorHeap) m_rtvHeap;
  UINT m_descriptorSize;
  
};
