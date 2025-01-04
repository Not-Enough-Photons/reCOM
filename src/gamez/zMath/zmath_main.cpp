#include <cmath>

#include "zmath.h"

float* sintbl = NULL;
float* costbl = NULL;
float* exptbl = NULL;

bool tableInit = false;

const CPnt3D CPnt3D::zero = { 0.0f, 0.0f, 0.0f };
const CQuat CQuat::identity = { CPnt3D(1.0f, 0.0f, 0.0f), 0.0f };
const CMatrix CMatrix::identity = {  };

void init_trig_table()
{
	if (!tableInit)
	{
		int i = 0;
		int j = 0;
		do
		{
			float x = i * 0.02454369f;
			float calc = sinf(x);
			*(sintbl + j) = calc;
			calc = cosf(x);
			*(costbl + j) = calc;
			i++;
			calc = expf(i * 10.0f) / 256.0f;
			*(exptbl + j) = calc;
			j += 4;
		} while (i < 257);
		tableInit = true;
	}
}

void uninit_trig_table()
{
	if (tableInit)
	{
		tableInit = false;
	}
}

CQuat CQuat::Apply(CQuat& quat, CPnt3D& point)
{
	// TODO:
	// what does THIS do?
	// the RE source has a bunch of inserted assembly instructions
	return CQuat();
}

CQuat CQuat::Normalize(CQuat& quat, CQuat& rhs)
{
	float placeholder = 0.0f;
	// float innerProduct = Vector3::Product(this, rhs);
	placeholder = sqrtf(quat.w * quat.w + placeholder);
	// Vector3::Scale(1.0 / placeholder, rhs, this);
	return CQuat();
}

CQuat CQuat::Mul(CQuat& left, CQuat& right)
{
	// TODO:
	// This will remain empty until I replace the proprietary VU calls with my own
	return CQuat();
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
		quat.vec.x = 0.0f;
		quat.vec.y = 0.0f;
		quat.vec.z = 0.0f;
	}
	else
	{
		pointLengthSqr = sqrtf(pointLengthSqr);
		float sin = sinf(pointLengthSqr);
		float cos = cosf(pointLengthSqr);
		quat.w = cos;
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
	out.vec.x = sinHalfX * zSin + halfX * sinHalfY * zCos;
	out.vec.y = sinHalfX * zCos - halfX * sinHalfY * zSin;
	out.vec.z = halfX * halfY * zSin - zMul * zCos;
}