#pragma once

#include "core/EngineCore.h"

#include "Shader.h"
#include "infra/pipeline/RootSignature.h"
#include <d3d12.h>

class PipelineState {
 public:
  void Create(D3D12_INPUT_ELEMENT_DESC* inputs, UINT count);
  void WithShader(Shared(Shader) shader, Shader::StageType type);
  void WithRootSignature(Shared(RootSignature) rootSignature);
  void Finalize();
  ComP(ID3D12PipelineState) GetPSO() const {return m_pso; };
 protected: 
  ComP(ID3D12PipelineState) m_pso;
  Shared(D3D12_GRAPHICS_PIPELINE_STATE_DESC) desc;
  bool hasFinished;
};
