#include <cmath>

#include "zmath_main.h"

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