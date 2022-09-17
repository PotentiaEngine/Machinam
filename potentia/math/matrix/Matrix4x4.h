#pragma once

#include "core/EngineCore.h"
#include <DirectXMath.h>

class Matrix4x4 {
public:
  XMMATRIX GetMatrix() const { return m_matrix; };

protected:
  XMMATRIX m_matrix;
};
