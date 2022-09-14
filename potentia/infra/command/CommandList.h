#pragma once

#include "core/EngineCore.h"
#include <d3d12.h>

class CommandList {
  public:
    void Create();
    ComP(ID3D12CommandList) GetCommandList() const { return m_commandList; }
    void Close();
  protected:
    ComP(ID3D12CommandList) m_commandList;
};
