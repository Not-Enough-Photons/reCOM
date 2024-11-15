#pragma once
void zMath_Init();

bool tableInit;

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

class CPnt2D
{
	float x;
	float y;
};

class CPnt3D
{
public:
	CPnt3D& operator+(const CPnt3D& vector);
	CPnt3D& operator-(const CPnt3D& vector);
	CPnt3D& operator*(float scalar);
	CPnt3D& operator/(float scalar);
public:
	PNT3D point;
public:
	void Normalize();
	void Normalize(CPnt3D* other);
	CPnt3D* Add(CPnt3D* other);
	CPnt3D* Sub(CPnt3D* other);
	void Scale(CPnt3D* other, float scaleFactor);
	void Cross(const CPnt3D* a, CPnt3D* b, bool normalize);
};

class CPnt4D
{
public:

public:
	PNT4D point;
};

class CQuat
{
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
	float m_matrix[4][4];
};

