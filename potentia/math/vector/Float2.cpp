#include "Float2.h"
#include <DirectXMath.h>


Float2 Float2::FromAPIVector(XMVECTOR vector) {
  Float2 f;
  f.m_vector = vector;
  return f;
}

Float2::Raw Float2::ToRaw() {
  Raw raw;
  raw.x = XMVectorGetX(m_vector);
  raw.y = XMVectorGetY(m_vector);
  return raw;
}
