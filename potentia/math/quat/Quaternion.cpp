#include "Quaternion.h"
#include <DirectXMath.h>

Quaternion Quaternion::FromAPIVector(XMVECTOR apiVector) {
  Quaternion quat;
  quat.m_vector = apiVector;
  return quat;
}

Quaternion Quaternion::BaryCentric(Quaternion q0, Quaternion q1, Quaternion q2, float f, float g) {
  return Quaternion::FromAPIVector(XMQuaternionBaryCentric(q0.m_vector, q1.m_vector, q2.m_vector, f, g));
}

Quaternion Quaternion::BaryCentricV(Quaternion q0, Quaternion q1, Quaternion q2, Float4 f, Float4 g) {
  return FromAPIVector(XMQuaternionBaryCentricV(q0.m_vector, q1.m_vector, q2.m_vector, f.GetVec(), g.GetVec()));
}

Quaternion Quaternion::Identity() {
  return FromAPIVector(XMQuaternionIdentity());
}

Quaternion Quaternion::RotationAxis(Float3 axis, float angle) {
  return FromAPIVector(XMQuaternionRotationAxis(axis.GetVec(), angle));
}

Quaternion Quaternion::RotationMatrix(Matrix4x4 mat) {
  return FromAPIVector(XMQuaternionRotationMatrix(mat.GetMatrix()));
}

Quaternion Quaternion::RotationNormal(Float4 axis, float angle) {
  return FromAPIVector(XMQuaternionRotationNormal(axis.GetVec(), angle));
}

Quaternion Quaternion::RollPitchYaw(float roll, float pitch, float yaw) {
  return FromAPIVector(XMQuaternionRotationRollPitchYaw(pitch, yaw, roll));
}

Quaternion Quaternion::RollPitchYawV(Float3 vector) {
  return FromAPIVector(XMQuaternionRotationRollPitchYawFromVector(vector.GetVec()));
}

Quaternion Quaternion::Slerp(Quaternion start, Quaternion end, float t) {
  return FromAPIVector(XMQuaternionSlerp(start.m_vector, end.m_vector, t));
}

Quaternion Quaternion::SlerpV(Quaternion start, Quaternion end, Float4 t) {
  return FromAPIVector(XMQuaternionSlerpV(start.m_vector, end.m_vector, t.GetVec()));
}

Quaternion Quaternion::Squad(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, float t) {
  return FromAPIVector(XMQuaternionSquad(q0.m_vector, q1.m_vector, q2.m_vector, q3.m_vector, t));
}

Quaternion Quaternion::SquadV(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, Float4 t) {
  return FromAPIVector(XMQuaternionSquadV(q0.m_vector, q1.m_vector, q2.m_vector, q3.m_vector, t.GetVec()));
}


