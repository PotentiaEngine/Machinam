#pragma once


#include "d3dx12.h"
#include "pch.h"
#include <d3dcommon.h>

class Shader {
  public:
    void Create(Str path, Str entrypoint);
    CD3DX12_SHADER_BYTECODE GetBytecode(); 
  private:
    cptr(ID3DBlob) m_blob;
};


