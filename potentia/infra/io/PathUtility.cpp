#include "PathUtility.h"
#include <filesystem>

std::string PathUtility::GetAssetPath(std::string relPath) {
  return std::filesystem::absolute(relPath).string();
}

