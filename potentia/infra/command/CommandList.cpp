#include "CommandList.h"
#include "core/EngineCore.h"
#include "infra/command/CommandAllocator.h"
#include "infra/devices/LogicalDevice.h"
#include "infra/pipeline/PipelineState.h"
#include <combaseapi.h>

void CommandList::Create(Shared(PipelineState) pso) {
  ThrowOnFail(LogicalDevice::Get()->GetDevice()->CreateCommandList(
      0, D3D12_COMMAND_LIST_TYPE_DIRECT,
      CommandAllocator::Get()->GetCommandAllocator().Get(), pso->GetPSO().Get(),
      IID_PPV_ARGS(&m_commandList)));
}

void CommandList::Close() { ThrowOnFail(m_commandList->Close()); }
