#pragma once
#include <cmath>

class CPnt2D;
class CPnt3D;
class CPnt4D;
class CQuat;
class CMatrix;

void zMath_Init();

bool tableInit;

const float PI = 3.141593;

float* sintbl;
float* costbl;
float* exptbl;

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
		} 
		while (i < 257);
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

template <typename T>
inline float min(T& first, T& second)
{
	if (second < first)
	{
		first = second;
	}

	return first;
}

template <typename T>
inline float max(T& first, T& second)
{
	if (first < second)
	{
		first = second;
	}

	return first;
}

template<typename T>
inline float decay(T base, T power, T& result, const T& original)
{
	float exp = expf(base * power);
	return result = original + (result - original) * exp;
}

template<typename T>
inline bool close_enough(T& value, T& min, T& max)
{
	return -max <= value - min || max < value - min;
}

template<typename T>
inline bool saturate(T& value, T min, T max)
{
	if (value > max)
	{
		value = max;
		return true;
	}
	else if (value < min)
	{
		value = min;
		return true;
	}

	return false;
}

struct Rfloat
{
	float m_min;
	float m_range;
};

struct PNT2D
{
	float x;
	float y;
};

struct PNT3D
{
	float x;
	float y;
	float z;
};

struct PNT4D
{
	float x;
	float y;
	float z;
	float w;
};

struct IPNT2D
{
	int x;
	int y;
};

struct IPNT3D
{
	int x;
	int y;
	int z;
};

struct IPNT4D
{
	int x;
	int y;
	int z;
	int w;
};

class CPnt2D : public PNT2D { };

class CPnt3D : public PNT3D
{
public:
	CPnt3D();
	CPnt3D(const CPnt3D& other);
	CPnt3D(float x, float y, float z);

	CPnt3D& operator+(const CPnt3D& vector);
	CPnt3D& operator-(const CPnt3D& vector);
	CPnt3D& operator*(float scalar);
	CPnt3D& operator/(float scalar);

	static const CPnt3D zero;
public:
	void Normalize();
	void Normalize(CPnt3D* other);
	CPnt3D* Add(CPnt3D* other);
	CPnt3D* Sub(CPnt3D* other);
	void Scale(CPnt3D* other, float scaleFactor);
	void Cross(const CPnt3D* a, CPnt3D* b, bool normalize);
};

class CPnt4D : public PNT4D { };

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
	static void MakeYXZ(float x, float y, float z, CQuat& quat);
public:
	CPnt3D vec;
	float w;
};

class CMatrix
{
public:
	static const CMatrix identity;

	const float* operator[](const int row);
public:
	const float* GetTranslate() const;

	void Multiply(const CMatrix* first, const CMatrix* second);

	void SetRotation(const CPnt3D* rotation);
	void SetRows(const CPnt3D* first, const CPnt3D* second, const CPnt3D* third, const CPnt3D* fourth);
	void SetZero();

	void ToEuler(CPnt3D* p);
	CQuat* ToQuat(CQuat* q);
public:
	float m_matrix[4][4];
};

class CBBox
{
public:
	CPnt3D m_min;
	CPnt3D m_max;
};

const CPnt3D CPnt3D::zero = { 0.0f, 0.0f, 0.0f };
const CQuat CQuat::identity = { CPnt3D(1.0f, 0.0f, 0.0f), 0.0f };
const CMatrix CMatrix::identity = {  };