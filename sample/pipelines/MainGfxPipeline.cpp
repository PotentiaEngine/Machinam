#include "MainGfxPipeline.h"
#include <potentia/core/macros.h>
#include <potentia/infra/pipeline/PipelineState.h>
#include <potentia/infra/resource/VertexBuffer.h>
#include <potentia/math/vector/Float3.h>
#include <potentia/structure/data/Vertex.h>

void MainGfxPipeline::Setup(Shared(PipelineState) pso) {
  inputs = std::vector<D3D12_INPUT_ELEMENT_DESC>();
  inputs.push_back({"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
       D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0});
  inputs.push_back({"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
       D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0});
  
  pso->Create(inputs.data(), inputs.size());
  m_rootSignature->CreateEmpty();
  pso->WithRootSignature(m_rootSignature);
  vs = MakeShared(Shader);
  ps = MakeShared(Shader);

  vs->Create("assets/Shader.hlsl", "VSMain", "vs_5_0");
  ps->Create("assets/Shader.hlsl", "PSMain", "ps_5_0");

  pso->WithShader(vs, Shader::Vertex);
  pso->WithShader(ps, Shader::Pixel);
}

void MainGfxPipeline::SetupResources() {
  auto vecVerts = MakeShared(std::vector<Vertex>);
  vecVerts->push_back({ { 0.0f, 0.25f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } });
  vecVerts->push_back({ { 0.25f, -0.25f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } });
  vecVerts->push_back({ { -0.25f, -0.25f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } });
  m_vertexBuffer = MakeShared(VertexBuffer);
  m_vertexBuffer->CreateBuffer(vecVerts);
}


void MainGfxPipeline::Render() {
  auto vbView = m_vertexBuffer->GetVertexBufferView();
  m_cmdList->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
  m_cmdList->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}
