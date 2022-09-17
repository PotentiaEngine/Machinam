#include "AbstractBuffer.h"
#include "core/EngineCore.h"
#include "core/d3dx12.h"
#include "infra/devices/LogicalDevice.h"
#include <cstring>

void AbstractBuffer::CreateResource(UINT size) {
  m_size = size;

  auto props = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
  auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(size);
  ThrowOnFail(LogicalDevice::Get()->GetDevice()->CreateCommittedResource(
      &props,
      D3D12_HEAP_FLAG_NONE,
      &resourceDesc,
      D3D12_RESOURCE_STATE_GENERIC_READ,
      nullptr,
      IID_PPV_ARGS(&m_buffer)));
}

void AbstractBuffer::Map(BYTE *data) {
  UINT8* pDataBegin;
  CD3DX12_RANGE readRange(0, 0);
  ThrowOnFail(m_buffer->Map(0, &readRange, reinterpret_cast<void**>(&pDataBegin)));
  std::memcpy(pDataBegin, data, m_size);
  m_buffer->Unmap(0, nullptr);
}
