#include <cmath>

#include "zmath_main.h"

void CPnt3D::Normalize(CPnt3D& self)
{
	float sqrMagnitude = sqrtf(self.z * self.z + self.x * self.x + self.y * self.y);

	if (sqrMagnitude != 0.0f)
	{
		sqrMagnitude = 1.0f / sqrMagnitude;
		self.x = self.x * sqrMagnitude;
		self.y = self.y * sqrMagnitude;
		self.z = self.z * sqrMagnitude;
	}
}

void CPnt3D::Normalize(CPnt3D& lhs, CPnt3D& rhs)
{
	float sqrMagnitude = sqrtf(lhs.z * lhs.z + lhs.x * lhs.x + lhs.y * lhs.y);

	if (sqrMagnitude != 0.0f)
	{
		sqrMagnitude = 1.0f / sqrMagnitude;
		rhs.x = lhs.x * sqrMagnitude;
		rhs.y = lhs.y * sqrMagnitude;
		rhs.z = lhs.z * sqrMagnitude;
	}
}

CPnt3D CPnt3D::Add(CPnt3D& first, CPnt3D& second)
{
	CPnt3D output;
	output.x = first.x + second.x;
	output.y = first.y + second.y;
	output.z = first.z + second.z;
	return output;
}

CPnt3D CPnt3D::Scale(float scaleFactor, CPnt3D& first, CPnt3D& second)
{
	first.x = second.x * scaleFactor;
	first.y = second.y * scaleFactor;
	first.z = second.z * scaleFactor;
}

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