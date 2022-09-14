#include "PathUtility.h"
#include <filesystem>

std::string PathUtility::GetAssetPath(std::string relPath) {
  auto path = std::filesystem::current_path();
  return path.append(relPath).string();
}

