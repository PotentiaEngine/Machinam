#pragma once

#include "core/EngineCore.h"
#include "math/vector/VectorBase.h"
#include <DirectXMath.h>

class Float2 : public VectorBase {
  public:
    static Float2 FromAPIVector(XMVECTOR vector);
    struct Raw {
      float x;
      float y;
    };
    Raw ToRaw();
};
