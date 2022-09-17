#pragma once

#include "core/EngineCore.h"
#include "core/macros.h"
#include "math/vector/WrappedXMVector.h"
#include <DirectXMath.h>

class Float3 : public WrappedXMVector {
  public:
    struct Raw {
      float x;
      float y;
      float z;
    };
    Raw ToRaw();
};
