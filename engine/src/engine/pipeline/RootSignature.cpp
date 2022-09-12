#include "RootSignature.h"

#include <combaseapi.h>
#include <d3d12.h>

#include "engine/devices/LogicalDevice.h"
#include "utils.h"

void RootSignature::CreateEmpty() {
  CD3DX12_ROOT_SIGNATURE_DESC desc = {};
  desc.Init(0, nullptr, 0, nullptr,
            D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

  cptr(ID3DBlob) signature;
  cptr(ID3DBlob) error;

  ThrowOnFail(D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1,
                                          &signature, &error));
  ThrowOnFail(LogicalDevice::Instance()->GetDevice()->CreateRootSignature(
      0, signature->GetBufferPointer(), signature->GetBufferSize(),
      IID_PPV_ARGS(&m_rootSignature)));
  
}
