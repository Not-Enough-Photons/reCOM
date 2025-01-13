#include <math.h>

#include "zmath.h"

void CPnt3D::Normalize()
{
	f32 sqrMagnitude = sqrtf(z * z + x * x + y * y);

	if (sqrMagnitude != 0.0f)
	{
		sqrMagnitude = 1.0f / sqrMagnitude;
		x *= sqrMagnitude;
		y *= sqrMagnitude;
		z *= sqrMagnitude;
	}
}

void CPnt3D::Normalize(CPnt3D* other)
{
	f32 sqrMagnitude = sqrtf(z * z + x * x + y * y);

	if (sqrMagnitude != 0.0f)
	{
		sqrMagnitude = 1.0f / sqrMagnitude;
		other->x = x * sqrMagnitude;
		other->y = y * sqrMagnitude;
		other->z = z * sqrMagnitude;
	}
}

CPnt3D* CPnt3D::Add(CPnt3D* other)
{
	CPnt3D* output;
	output->x = x + other->x;
	output->y = y + other->y;
	output->z = z + other->z;
	return output;
}

CPnt3D* CPnt3D::Sub(CPnt3D* other)
{
	CPnt3D* output;
	output->x = x - other->x;
	output->y = y - other->y;
	output->z = z - other->z;
	return output;
}

void CPnt3D::Scale(CPnt3D* other, f32 scaleFactor)
{
	other->x = x * scaleFactor;
	other->y = y * scaleFactor;
	other->z = z * scaleFactor;
}

void CPnt3D::Cross(const CPnt3D* a, CPnt3D* b, bool normalize)
{

}