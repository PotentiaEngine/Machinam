#pragma once

#include "core/EngineCore.h"
#include "core/macros.h"
#include "infra/command/CommandList.h"
#include "infra/pipeline/PipelineState.h"
#include "infra/pipeline/RootSignature.h"

class GraphicsPipeline {
  public:
    void RenderAll();
    void Setup();
    virtual void Setup(Shared(PipelineState) pso);
    virtual void SetupResources();
    virtual void Render();
  protected:
    Shared(PipelineState) m_pso;
    Shared(CommandList) m_cmdList;
    Shared(RootSignature) m_rootSignature;
};
