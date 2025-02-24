#pragma once
#include <cmath>

#include "gamez/zSystem/zsys.h"

class CPnt2D;
class CPnt3D;
class CPnt4D;
class CQuat;
class CMatrix;

void zMath_Init();

extern bool tableInit;

const f32 PI = 3.141593f;
const f32 RAD_TO_DEG = 0.01745329;

extern f32* sintbl;
extern f32* costbl;
extern f32* exptbl;

void init_trig_table();
void uninit_trig_table();

template <typename T>
float min(T& first, T& second)
{
	if (second < first)
	{
		first = second;
	}

	return first;
}

template <typename T>
float max(T& first, T& second)
{
	if (first < second)
	{
		first = second;
	}

	return first;
}

template<typename T>
float decay(T base, T power, T& result, const T& original)
{
	float exp = expf(base * power);
	return result = original + (result - original) * exp;
}

template<typename T>
bool close_enough(T& value, T& min, T& max)
{
	return -max <= value - min || max < value - min;
}

template<typename T>
bool saturate(T& value, T min, T max)
{
	if (value > max)
	{
		value = max;
		return true;
	}

	if (value < min)
	{
		value = min;
		return true;
	}

	return false;
}

struct Rfloat
{
	f32 m_min;
	f32 m_range;
};

struct PNT2D
{
	f32 x;
	f32 y;
};

struct PNT3D
{
	f32 x;
	f32 y;
	f32 z;
};

struct PNT4D
{
	f32 x;
	f32 y;
	f32 z;
	f32 w;
};

struct IPNT2D
{
	s32 x;
	s32 y;
};

struct IPNT3D
{
	s32 x;
	s32 y;
	s32 z;
};

struct IPNT4D
{
	s32 x;
	s32 y;
	s32 z;
	s32 w;
};

class CPnt2D : public PNT2D { };

class CPnt3D : public PNT3D
{
public:
	CPnt3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	CPnt3D(const CPnt3D& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	CPnt3D(f32 x, f32 y, f32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	CPnt3D& operator+(const CPnt3D& vector);
	CPnt3D& operator-(const CPnt3D& vector);
	CPnt3D& operator*(f32 scalar);
	CPnt3D& operator/(f32 scalar);

	static const CPnt3D zero;
	static const CPnt3D unit_nz;

	void Normalize();
	void Normalize(CPnt3D* other);
	void Add(const CPnt3D* other, CPnt3D* out);
	void Sub(const CPnt3D* other, CPnt3D* out);
	void Scale(CPnt3D* other, f32 scaleFactor);
	void Cross(const CPnt3D* a, CPnt3D* b, bool normalize);
};

class CPnt4D : public PNT4D
{
public:
	CPnt4D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	CPnt4D(const CPnt4D& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	CPnt4D(f32 x, f32 y, f32 z, f32 w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	CPnt4D& operator=(const CPnt4D& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		return *this;
	}
	
	static const CPnt4D zero;
};

class CQuat
{
public:
	static const CQuat identity;
public:
	static CQuat Apply(CQuat& quat, CPnt3D& point);
	static CQuat Normalize(CQuat& quat, CQuat& rhs);
	static CQuat Mul(CQuat& left, CQuat& right);
	static void ToMatrix(CQuat& quat, CMatrix& matrix);
	static CQuat Exp(CQuat& quat, CPnt3D& point);
	static void MakeYXZ(f32 x, f32 y, f32 z, CQuat& quat);
public:
	CPnt3D vec;
	f32 w;
};

class CMatrix
{
public:
	static const CMatrix identity;

	const float* operator[](const s32 row);
public:
	const float* GetTranslate() const;

	void Transform(CPnt3D* point, s32 count) const;
	void Multiply(const CMatrix* first, const CMatrix* second);

	void SetRotation(const CPnt3D* rotation);
	void SetRows(const CPnt3D* first, const CPnt3D* second, const CPnt3D* third, const CPnt3D* fourth);
	void SetZero();

	void ToEuler(CPnt3D* p);
	CQuat* ToQuat(CQuat* q);
public:
	f32 m_matrix[4][4];
};

class CBBox
{
public:
	CPnt3D m_min;
	CPnt3D m_max;
};

class CFRect
{
public:
	f32 top;
	f32 bottom;
	f32 left;
	f32 right;
};