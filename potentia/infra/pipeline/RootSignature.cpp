#include "RootSignature.h"

#include "infra/devices/LogicalDevice.h"

void RootSignature::CreateEmpty() {
  CD3DX12_ROOT_SIGNATURE_DESC desc = {};
  desc.Init(0, nullptr, 0, nullptr,
            D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

  ComP(ID3DBlob) signature;
  ComP(ID3DBlob) error;

  ThrowOnFail(D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1,
                                          &signature, &error));
  ThrowOnFail(LogicalDevice::Get()->GetDevice()->CreateRootSignature(
      0, signature->GetBufferPointer(), signature->GetBufferSize(),
      IID_PPV_ARGS(&m_rootSignature)));
  
}
