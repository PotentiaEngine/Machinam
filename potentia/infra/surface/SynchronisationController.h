#pragma once

#include "core/EngineCore.h"
#include "core/base/Singleton.h"

class SynchronisationController : public Singleton<SynchronisationController> {
 public:
  void Create();
  void WaitForGPU();
  Getter(UINT, FrameCount, c_frameCount);
  Getter(UINT, FrameIndex, m_frameIndex);
  void SetFrameIndex(UINT index) { m_frameIndex = index; }
  static const UINT c_frameCount = 2;
 private:
  ComP(ID3D12Fence) m_fence;
  UINT m_frameIndex;
  UINT64 m_fenceValue;
  HANDLE m_fenceEvent;
};

#define Sync SynchronisationController
