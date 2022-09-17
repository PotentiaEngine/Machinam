#pragma once

#include "core/EngineCore.h"

class WrappedXMVector {
  public:
    XMVECTOR GetVec() const { return m_vector; }
    void Set(XMVECTOR inner) { m_vector = XMVECTOR(); };
  protected:
    XMVECTOR m_vector;
};
