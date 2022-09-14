#pragma once
#include "core/EngineCore.h"


class Shader {
  public:
    void Create(std::string path, std::string entrypoint);
    CD3DX12_SHADER_BYTECODE GetBytecode(); 
    enum StageType {
      Vertex,
      Pixel,
      Domain,
      Geometry
    };
  private:
    ComP(ID3DBlob) m_blob;
  
};


