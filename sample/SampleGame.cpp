#include "SampleGame.h"
#include "core/macros.h"
#include "infra/pipeline/PipelineState.h"
#include "infra/pipeline/RootSignature.h"
#include "infra/pipeline/Shader.h"
#include "structure/GameInstance.h"

void SampleGame::RegisterRoot() {
  D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
      {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
       D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
      {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
       D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}};

  auto pso = MakeShared(PipelineState);
  auto rootSig = MakeShared(RootSignature);
  pso->Create(inputElementDescs, 2);
      pso->WithRootSignature(rootSig);
  auto vs = MakeShared(Shader);
  auto ps = MakeShared(Shader);

  vs->Create("../assets/Shader.hlsl", "VSMain");
  ps->Create("../assets/Shader.hlsl", "PSMain");

  pso->WithShader(vs, Shader::Vertex);
  pso->WithShader(ps, Shader::Pixel);
  RegisterPSO(pso);
}

