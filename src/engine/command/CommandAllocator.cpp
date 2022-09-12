#include "CommandAllocator.h"

#include <combaseapi.h>
#include <d3d12.h>

#include "engine/base/Singleton.h"
#include "engine/devices/LogicalDevice.h"
#include "utils.h"


void CommandAllocator::Create() {
  ThrowOnFail(LogicalDevice::Instance()->GetDevice()->CreateCommandAllocator(
      D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator)));
}
