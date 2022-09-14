#pragma once
#include "core/EngineCore.h"
#include "core/base/Singleton.h"

class CommandQueue : public Singleton<CommandQueue> {
public:
  void Create(D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT);
  Getter(ComP(ID3D12CommandQueue), CommandQueue, m_commandQueue);
  
private:
  ComP(ID3D12CommandQueue) m_commandQueue;
};
