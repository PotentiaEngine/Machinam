#include "Shader.h"

#include "core/macros.h"
#include "infra/io/PathUtility.h"
#include <d3dcommon.h>

void Shader::Create(std::string path, std::string entrypoint, std::string version) {
  auto str = PathUtility::Get()->GetAssetPath(path);
  auto wstr = std::wstring(str.begin(), str.end());

  ID3DBlob* errors;
  ThrowOnFail(
      D3DCompileFromFile(wstr.c_str(),
                         nullptr, nullptr, entrypoint.c_str(), version.c_str(), 0, 0, &m_blob, &errors));
}

CD3DX12_SHADER_BYTECODE Shader::GetBytecode() {
  return CD3DX12_SHADER_BYTECODE(m_blob.Get());
}
