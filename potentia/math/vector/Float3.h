#pragma once

#include "core/EngineCore.h"
#include "core/macros.h"
#include "math/vector/VectorBase.h"
#include <DirectXMath.h>

class Float3 : public VectorBase {
  public:
    struct Raw {
      float x;
      float y;
      float z;
    };
    Raw ToRaw();
};
