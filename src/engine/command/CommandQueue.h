#pragma once

#include "pch.h"
#include "engine/base/Singleton.h"

class CommandQueue : public Singleton<CommandQueue>{
public:
  void Create(D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT);
  Getter(cptr(d3d(CommandQueue)), CommandQueue, m_commandQueue);
  
private:
  cptr(d3d(CommandQueue)) m_commandQueue;
};
