#pragma once

#include "core/EngineCore.h"

class VectorBase {
  public:
    XMVECTOR GetVec() const { return m_vector; }
    void Set(XMVECTOR inner) { m_vector = inner; };
  protected:
    XMVECTOR m_vector;
};
