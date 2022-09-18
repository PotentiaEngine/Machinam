#pragma once

#include "core/EngineCore.h"
#include "math/vector/VectorBase.h"

class Float2 : public VectorBase {
  public:
    struct Raw {
      float x;
      float y;
    };
    Raw ToRaw();
};
