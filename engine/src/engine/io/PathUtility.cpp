#include "PathUtility.h"
#include <libloaderapi.h>
#include <minwindef.h>
#include <stdlib.h>
#include <winnt.h>
#include <wrl/wrappers/corewrappers.h>
#include <filesystem>

Str PathUtility::GetAssetPath(Str relPath) {
  auto path = std::filesystem::current_path();
  return path.append(relPath).string();
}

