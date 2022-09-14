#pragma once
#include "core/EngineCore.h"
#include "core/base/Singleton.h"

class CommandAllocator : public Singleton<CommandAllocator> {
 public:
  void Create();
  Getter(ComP(ID3D12CommandAllocator), CommandAllocator, m_commandAllocator);

 private:
  ComP(ID3D12CommandAllocator) m_commandAllocator;
};
