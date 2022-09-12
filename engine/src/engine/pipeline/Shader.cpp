#include "Shader.h"

#include <D3Dcompiler.h>
#include <fileapi.h>
#include <string>
#include <winbase.h>

#include "d3dx12.h"
#include "engine/io/PathUtility.h"
#include "utils.h"

void Shader::Create(Str path, Str entrypoint) {
  auto str = PathUtility::Instance()->GetAssetPath(path);
  auto wstr = WStr(str.begin(), str.end());

  ThrowOnFail(
      D3DCompileFromFile(wstr.c_str(),
                         nullptr, nullptr, "VSMain", "vs_5.0", 0, 0, &m_blob, nullptr));

}


CD3DX12_SHADER_BYTECODE Shader::GetBytecode() {
  return CD3DX12_SHADER_BYTECODE(m_blob.Get());
}
