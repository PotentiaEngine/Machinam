#pragma once

#include "pch.h"
#include "engine/base/Singleton.h"

class PathUtility: public Singleton<PathUtility> {
  public:
    Str GetAssetPath(Str relPath);
};
