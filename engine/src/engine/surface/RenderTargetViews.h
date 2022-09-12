#pragma once

#include "engine/base/Singleton.h"
#include "engine/surface/SynchronisationController.h"

class RenderTargetViews : public Singleton<RenderTargetViews> {
 public:
  void Create();
  cptr(d3d(Resource)) GetRTV(UINT frameIndex) const {
    return m_renderTargets[frameIndex];
  } 
 protected:
  cptr(d3d(Resource)) m_renderTargets[SynchronisationController::c_frameCount];
  cptr(d3d(DescriptorHeap)) m_rtvHeap;
  UINT m_descriptorSize;
  
};
