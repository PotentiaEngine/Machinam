#pragma once

#include "core/EngineCore.h"
#include <d3d12.h>

class RootSignature {
public: 
  void CreateEmpty();
  ComP(ID3D12RootSignature) GetRootSignature() const {return m_rootSignature;};
private:
  ComP(ID3D12RootSignature) m_rootSignature;
};
