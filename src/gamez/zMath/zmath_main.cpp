#include <cmath>

#include "zmath_main.h"


CQuat CQuat::Apply(CQuat& quat, CPnt3D& point)
{
	// TODO:
	// what does THIS do?
	// the RE source has a bunch of inserted assembly instructions
}

CQuat CQuat::Normalize(CQuat& quat, CQuat& rhs)
{
	float placeholder = 0.0f;
	// float innerProduct = Vector3::Product(this, rhs);
	placeholder = sqrtf(quat.w * quat.w + placeholder);
	// Vector3::Scale(1.0 / placeholder, rhs, this);
}

CQuat CQuat::Mul(CQuat& left, CQuat& right)
{
	// TODO:
	// This will remain empty until I replace the proprietary VU calls with my own
}

void CQuat::ToMatrix(CQuat& quat, CMatrix& matrix)
{
	// TODO:
	// Port matrix quaternion to matrix conversion function
}

CQuat CQuat::Exp(CQuat& quat, CPnt3D& point)
{
	float pointLengthSqr = point.z * point.z + point.y * point.y + point.x * point.x;

	if (pointLengthSqr == 0.0f)
	{
		quat.w = 1.0f;
		quat.x = 0.0f;
		quat.y = 0.0f;
		quat.z = 0.0f;
	}
	else
	{
		pointLengthSqr = sqrtf(pointLengthSqr);
		float sin = sinf(pointLengthSqr);
		float cos = cosf(pointLengthSqr);
		quat.w = cos;
		// what a bunch of fucking bull fuck
		CPnt3D::Scale(sin / pointLengthSqr, point, reinterpret_cast<CPnt3D&>(quat));
	}

	return quat;
}

void CQuat::MakeYXZ(float x, float y, float z, CQuat& out)
{
	float halfX = x * 0.5f;
	float sinHalfX = sinf(halfX);
	halfX = cosf(halfX);

	float halfY = x * 0.5f;
	float sinHalfY = sinf(halfY);
	halfY = cosf(halfY);

	float zMul = sinHalfX * sinHalfY;
	sinHalfX *= halfY;

	float zSin = sinf(z * 0.5f);
	float zCos = cosf(z * 0.5f);

	out.w = zMul * zSin + halfX * halfY * zCos;
	out.x = sinHalfX * zSin + halfX * sinHalfY * zCos;
	out.y = sinHalfX * zCos - halfX * sinHalfY * zSin;
	out.z = halfX * halfY * zSin - zMul * zCos;
}