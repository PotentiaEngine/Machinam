#pragma once

#include "pch.h"

class RootSignature {
public: 
  void CreateEmpty();
private:
  cptr(d3d(RootSignature)) m_rootSignature;
};
