#pragma once

#include "core/EngineCore.h"
#include "core/macros.h"
#include "infra/pipeline/PipelineState.h"

class CommandList {
  public:
    void Create(Shared(PipelineState) pso);
    ComP(ID3D12GraphicsCommandList) GetCommandList() const { return m_commandList; }
    void Close();
  protected:
    ComP(ID3D12GraphicsCommandList) m_commandList;
};
