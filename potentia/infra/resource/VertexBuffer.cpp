#include "VertexBuffer.h"
#include "structure/data/Vertex.h"

void VertexBuffer::CreateBuffer(std::shared_ptr<std::vector<Vertex>> vertices) {
  CreateResource(sizeof(Vertex) * vertices->size());
  Map(reinterpret_cast<BYTE *>(vertices->data()));

  m_bufferView.SizeInBytes = m_size;
  m_bufferView.StrideInBytes = sizeof(Vertex);
  m_bufferView.BufferLocation = m_buffer->GetGPUVirtualAddress();
}
