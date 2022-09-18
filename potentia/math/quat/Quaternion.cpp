#include "Quaternion.h"
#include "math/vector/Float4.h"
#include <DirectXMath.h>

Quaternion Quaternion::FromAPIVector(XMVECTOR apiVector) {
  Quaternion quat;
  quat.m_vector = apiVector;
  return quat;
}

Quaternion Quaternion::BaryCentric(Quaternion q0, Quaternion q1, Quaternion q2, float f, float g) {
  return FromAPIVector(XMQuaternionBaryCentric(q0.m_vector, q1.m_vector, q2.m_vector, f, g));
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

Quaternion& Quaternion::Conjugate() {
  return SetVectorChainable(XMQuaternionConjugate(m_vector));
}

Quaternion& Quaternion::Exp() {
  return SetVectorChainable(XMQuaternionExp(m_vector));
}

Quaternion& Quaternion::ToIdentity() {
  return SetVectorChainable(Identity().m_vector);
}

Quaternion& Quaternion::Inverse() {
  return SetVectorChainable(XMQuaternionInverse(m_vector));
}

bool Quaternion::IsIdentity() {
  return XMQuaternionIsIdentity(m_vector);
}

bool Quaternion::IsInfinite() {
  return XMQuaternionIsInfinite(m_vector);
}

bool Quaternion::ISNaN() {
  return XMQuaternionIsNaN(m_vector);
}

Float4 Quaternion::Length() {
  return Float4::FromAPIVector(XMQuaternionLength(m_vector));
}

Float4 Quaternion::LengthSquared() {
  return Float4::FromAPIVector(XMQuaternionLengthSq(m_vector));
}

Float4 Quaternion::NaturalLog() {
  return Float4::FromAPIVector(XMQuaternionLn(m_vector));
}

Quaternion& Quaternion::Normalize() {
  return SetVectorChainable(XMQuaternionNormalize(m_vector));
}

Quaternion& Quaternion::NormalizeEst() {
  return SetVectorChainable(XMQuaternionNormalizeEst(m_vector));
}

Quaternion& Quaternion::ReciprocalLength() {
  return SetVectorChainable(XMQuaternionReciprocalLength(m_vector));
}

Float4 Quaternion::ToAxisAngle() {
  XMVECTOR axis;
  float angle;
  XMQuaternionToAxisAngle(&axis, &angle, m_vector);
  return Float4::FromAPIVector(XMVectorSet(XMVectorGetX(axis), XMVectorGetY(axis), XMVectorGetZ(axis), angle));
}

Quaternion& Quaternion::Dot(Quaternion other) {
  return SetVectorChainable(XMQuaternionDot(m_vector, other.m_vector));
}

bool Quaternion::Equal(Quaternion other) {
  return XMQuaternionEqual(m_vector, other.m_vector);
}

Quaternion& Quaternion::Multiply(Quaternion other) {
  return SetVectorChainable(XMQuaternionMultiply(m_vector, other.m_vector));
}

bool Quaternion::NotEqual(Quaternion other) {
  return XMQuaternionNotEqual(m_vector, other.m_vector);
}

Quaternion& Quaternion::SetVectorChainable(XMVECTOR vector) {
  m_vector = vector;
  return *this;
}
