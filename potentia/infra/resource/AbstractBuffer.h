#pragma once

#include "core/EngineCore.h"
#include "infra/command/CommandList.h"
#include <d3d12.h>

class AbstractBuffer {
  public:
    void CreateResource(UINT size);
    void Map(BYTE* data);
    
  protected:
    ComP(ID3D12Resource) m_buffer; 
    UINT m_size;
};
