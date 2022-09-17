#include "Float4.h"

Float4::Raw Float4::ToRaw() {
  auto x = XMVectorGetX(m_vector);
  auto y = XMVectorGetY(m_vector);
  auto z = XMVectorGetZ(m_vector);
  auto w = XMVectorGetW(m_vector);
  return {x, y, z, w};
}
