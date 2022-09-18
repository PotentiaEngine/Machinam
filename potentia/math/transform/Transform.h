#pragma once

#include "core/EngineCore.h"
#include "math/quat/Quaternion.h"
#include "math/vector/Float3.h"

class Transform {
public:
  Float3 worldPosition;
  Float3 localScale;
  Float3 globalScale;
  Quaternion localRotation;
  Quaternion globalRotation;
};
