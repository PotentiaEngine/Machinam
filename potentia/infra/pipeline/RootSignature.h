#pragma once

#include "core/EngineCore.h"

class RootSignature {
public: 
  void CreateEmpty();
private:
  ComP(ID3D12RootSignature) m_rootSignature;
};
