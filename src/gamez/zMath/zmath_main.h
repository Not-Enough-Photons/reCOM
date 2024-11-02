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

typedef struct CPnt2D
{
	float x;
	float y;
};

typedef struct CPnt3D
{
	float x;
	float y;
	float z;

	static void Normalize(CPnt3D& self);
	static void Normalize(CPnt3D& lhs, CPnt3D& rhs);
	static CPnt3D Add(CPnt3D& first, CPnt3D& second);
	static CPnt3D Sub(CPnt3D& first, CPnt3D& second);
	static CPnt3D Scale(float scaleFactor, CPnt3D& first, CPnt3D& second);
};

typedef struct CPnt4D
{
	float x;
	float y;
	float z;
	float w;
};

typedef struct CQuat
{
	float x;
	float y;
	float z;
	float w;

	static CQuat Apply(CQuat& quat, CPnt3D& point);
	static CQuat Normalize(CQuat& quat, CQuat& rhs);
	static CQuat Mul(CQuat& left, CQuat& right);
	static void ToMatrix(CQuat& quat, CMatrix& matrix);
	static CQuat Exp(CQuat& quat, CPnt3D& point);
	static void MakeYXZ(float x, float y, float z, CQuat& quat);
};

typedef union CMatrix
{
	struct
	{
		CPnt4D r0;
		CPnt4D r1;
		CPnt4D r2;
		CPnt4D r3;
	};

	float m[4][4];
};