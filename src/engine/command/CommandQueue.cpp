#include "CommandQueue.h"

#include <combaseapi.h>

#include "engine/devices/LogicalDevice.h"

void CommandQueue::Create(D3D12_COMMAND_LIST_TYPE type) {
  D3D12_COMMAND_QUEUE_DESC desc = {};
  desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  desc.Type = type;

  ThrowOnFail(LogicalDevice::Instance()->GetDevice()->CreateCommandQueue(
      &desc, IID_PPV_ARGS(&m_commandQueue)));
}
