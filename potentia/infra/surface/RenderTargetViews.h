#pragma once

#include "core/base/Singleton.h"
#include "SynchronisationController.h"
#include <d3d12.h>

class RenderTargetViews : public Singleton<RenderTargetViews> {
 public:
  void Create();
  UINT GetDescriptorSize() const {return m_descriptorSize; };
  ComP(ID3D12Resource) GetRTV(UINT frameIndex) const {
    return m_renderTargets[frameIndex];
  } 

  ComP(ID3D12DescriptorHeap) GetHeap() {
    return m_rtvHeap;
  }
 protected:
  ComP(ID3D12Resource) m_renderTargets[SynchronisationController::c_frameCount];
  ComP(ID3D12DescriptorHeap) m_rtvHeap;
  UINT m_descriptorSize;
  
};
