#pragma once

#include "core/EngineCore.h"
#include "math/matrix/Matrix4x4.h"
#include "math/vector/Float3.h"
#include "math/vector/Float4.h"
#include <DirectXMath.h>

class Quaternion {
  public:
    // static
    static Quaternion FromAPIVector(XMVECTOR apiVector);
    static Quaternion BaryCentric(Quaternion q0, Quaternion q1, Quaternion q2, float f, float g);
    static Quaternion BaryCentricV(Quaternion q0, Quaternion q1, Quaternion q2, Float4 f, Float4 g);
    static Quaternion Identity();
    static Quaternion RotationAxis(Float3 axis, float angle);
    static Quaternion RotationMatrix(Matrix4x4 mat);
    static Quaternion RotationNormal(Float4 axis, float angle);
    static Quaternion RollPitchYaw(float roll, float pitch, float yaw);
    static Quaternion RollPitchYawV(Float3 vector);
    static Quaternion Slerp(Quaternion start, Quaternion end, float t);
    static Quaternion SlerpV(Quaternion start, Quaternion end, Float4 t);
    static Quaternion Squad(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, float t);
    static Quaternion SquadV(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, Float4 t);

    // converting constructors 

    // To Self
    Quaternion& Conjugate();
    Quaternion& Exp();
    Quaternion& ToIdentity();
    Quaternion& Inverse();
    bool IsIdentity();
    bool IsInfinite();
    bool ISNaN();
    Float4 Length();
    Float4 LengthSquared();
    Float4 NaturalLog();
    Quaternion& Normalize();
    Quaternion& NormalizeEst();
    Quaternion& ReciprocalLength();
    Float4 ToAxisAngle();
    
    // To Self with other(s)
    Quaternion& Dot(Quaternion other);
    bool Equal(Quaternion other);
    Quaternion& Multiply(Quaternion other);
    bool NotEqual(Quaternion other);
    // operators
    Quaternion& operator*(Quaternion other) {
      return Multiply(other);
    }

  protected:
    XMVECTOR m_vector;
};
