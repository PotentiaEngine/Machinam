#pragma once

#include "core/EngineCore.h"
#include "core/macros.h"
#include "math/vector/WrappedXMVector.h"

class Float4 : public WrappedXMVector {
  public:
    struct Raw {
      float x;
      float y;
      float z;
      float w;
    };
    Raw ToRaw();
};
