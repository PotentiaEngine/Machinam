#pragma once

#include "core/EngineCore.h"
#include "infra/command/CommandList.h"

class AsbtractBuffer {
  public:
    void Create(UINT size, BYTE* data, D3D12_RESOURCE_STATES states, Shared(CommandList) cmdList);
};
