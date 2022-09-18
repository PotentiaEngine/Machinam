#include "Float2.h"
#include <DirectXMath.h>


Float2::Raw Float2::ToRaw() {
  Raw raw;
  raw.x = XMVectorGetX(m_vector);
  raw.y = XMVectorGetY(m_vector);
  return raw;
}
