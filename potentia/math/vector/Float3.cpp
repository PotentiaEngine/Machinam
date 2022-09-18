#include "Float3.h"
#include "math/vector/Float4.h"

Float3::Raw Float3::ToRaw() {
  auto x = XMVectorGetX(m_vector);
  auto y = XMVectorGetY(m_vector);
  auto z = XMVectorGetZ(m_vector);
  return {x, y, z};
}

Float3 Float3::FromAPIVector(XMVECTOR vector) {
  Float3 f;
  f.Set(vector);
  return f;
}
