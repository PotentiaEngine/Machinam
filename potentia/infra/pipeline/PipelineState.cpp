#include "PipelineState.h"
#include "core/EngineCore.h"
#include "core/d3dx12.h"
#include "core/macros.h"
#include "infra/devices/LogicalDevice.h"
#include <combaseapi.h>
#include <d3d12.h>
#include <dxgiformat.h>
#include <stdlib.h>

void PipelineState::Create(D3D12_INPUT_ELEMENT_DESC *inputs, UINT count) {
  desc = MakeShared(D3D12_GRAPHICS_PIPELINE_STATE_DESC);
  desc->InputLayout = {inputs, count};
  desc->RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
  desc->BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
  desc->DepthStencilState.DepthEnable = FALSE;
  desc->DepthStencilState.StencilEnable = FALSE;
  desc->SampleMask = UINT_MAX;
  desc->PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
  desc->NumRenderTargets = 1;
  desc->RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc->SampleDesc.Count = 1;
  desc->Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
}

void PipelineState::WithShader(std::shared_ptr<Shader> shader,
                               Shader::StageType type) {
  switch (type) {
  case Shader::StageType::Vertex:
    desc->VS = shader->GetBytecode();
    return;
  case Shader::StageType::Pixel:
    desc->PS = shader->GetBytecode();
    return;
  }
}

void PipelineState::WithRootSignature(
    std::shared_ptr<RootSignature> rootSignature) {
  desc->pRootSignature = rootSignature->GetRootSignature().Get();
}

void PipelineState::Finalize() {
  if (!hasFinished) {
    ThrowOnFail(LogicalDevice::Get()->GetDevice()->CreateGraphicsPipelineState(
        desc.get(), IID_PPV_ARGS(&m_pso)));
    hasFinished = true;
  }
}
