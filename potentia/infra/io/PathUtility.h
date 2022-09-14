#pragma once

#include "core/EngineCore.h"
#include  "core/base/Singleton.h"

class PathUtility: public Singleton<PathUtility> {
  public:
    std::string GetAssetPath(std::string relPath);
};
