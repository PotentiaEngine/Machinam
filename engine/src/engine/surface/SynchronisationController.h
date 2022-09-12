#pragma once

#include "engine/base/Singleton.h"
#include "pch.h"

class SynchronisationController : public Singleton<SynchronisationController> {
 public:
  void Create();
  void WaitForGPU();
  Getter(UINT, FrameCount, c_frameCount);
  Getter(UINT, FrameIndex, m_frameIndex);
  void SetFrameIndex(UINT index) { m_frameIndex = index; }
  static const UINT c_frameCount = 3;
 private:
  cptr(d3d(Fence)) m_fence;
  UINT m_frameIndex;
};

#define Sync SynchronisationController
