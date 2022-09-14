#include "Shader.h"

#include "infra/io/PathUtility.h"

void Shader::Create(std::string path, std::string entrypoint) {
  auto str = PathUtility::Get()->GetAssetPath(path);
  auto wstr = std::wstring(str.begin(), str.end());

  ThrowOnFail(
      D3DCompileFromFile(wstr.c_str(),
                         nullptr, nullptr, "VSMain", "vs_5.0", 0, 0, &m_blob, nullptr));

}


CD3DX12_SHADER_BYTECODE Shader::GetBytecode() {
  return CD3DX12_SHADER_BYTECODE(m_blob.Get());
}
