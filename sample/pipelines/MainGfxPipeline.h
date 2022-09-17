#pragma once

#include <potentia/core/EngineCore.h>
#include <potentia/core/macros.h>
#include <potentia/infra/resource/VertexBuffer.h>
#include <potentia/structure/pipeline/GraphicsPipeline.h>

class MainGfxPipeline : public GraphicsPipeline {
 void Setup(std::shared_ptr<PipelineState> pso) override;
 void SetupResources() override;
 void Render() override;
  protected:
 Shared(VertexBuffer) m_vertexBuffer;
  Shared(Shader) vs;
  Shared(Shader) ps;
  std::vector<D3D12_INPUT_ELEMENT_DESC> inputs;
};
