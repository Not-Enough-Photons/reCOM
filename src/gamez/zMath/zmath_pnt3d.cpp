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

void CPnt3D::Add(const CPnt3D* other, CPnt3D* out)
{
	out->x = x + other->x;
	out->y = y + other->y;
	out->z = z + other->z;
}

void CPnt3D::Sub(const CPnt3D* other, CPnt3D* out)
{
	out->x = x - other->x;
	out->y = y - other->y;
	out->z = z - other->z;
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