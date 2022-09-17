#pragma once

#include "core/EngineCore.h"
#include "AbstractBuffer.h"
#include "core/macros.h"
#include "structure/data/Vertex.h"
#include <vector>

class VertexBuffer : AbstractBuffer {
  public:
    void CreateBuffer(Shared(std::vector<Vertex>) vertices);
    Getter(D3D12_VERTEX_BUFFER_VIEW, VertexBufferView, m_bufferView);
  protected:
    D3D12_VERTEX_BUFFER_VIEW m_bufferView;
};
