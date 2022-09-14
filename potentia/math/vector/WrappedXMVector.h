#pragma once

#include "core/EngineCore.h"

class WrappedXMVector {
  public:
    Shared(XMVECTOR) GetVec() const { return m_vector; }
    void Set(XMVECTOR inner) { m_vector = MakeShared(XMVECTOR, inner); };
  protected:
    Shared(XMVECTOR) m_vector;
};
