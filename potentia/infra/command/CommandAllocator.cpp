#include "CommandAllocator.h"

#include "infra/devices/LogicalDevice.h"


void CommandAllocator::Create() {
  ThrowOnFail(LogicalDevice::Get()->GetDevice()->CreateCommandAllocator(
      D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator)));
}
