#pragma once
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

	static CPnt3D Add(CPnt3D& first, CPnt3D& second);
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