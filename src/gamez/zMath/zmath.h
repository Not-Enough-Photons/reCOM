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

extern f32* sintbl;
extern f32* costbl;
extern f32* exptbl;

void init_trig_table();
void uninit_trig_table();

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
public:
	void Normalize();
	void Normalize(CPnt3D* other);
	CPnt3D* Add(CPnt3D* other);
	CPnt3D* Sub(CPnt3D* other);
	void Scale(CPnt3D* other, f32 scaleFactor);
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

enum CDIType
{
	type_00,
	type_01,
	type_02,
	type_03,
	type_04
};

namespace zdb
{
	class CNode;
	class CSaveLoad;

	struct DI_PARAMS
	{
		CPnt4D m_nrm;

		s32 m_region;
		s32 m_refcount;

		s8 m_ditype;
		s32 m_ptcount;
		s32 m_material;

		s8 m_cameratype;

		s8 m_appflags;

		bool m_inside;
		bool m_shadow;

		s32 m_reserved;
	};

	class CDI
	{
	public:
		CDI();
		~CDI();

		static void* Create(CSaveLoad& saveload);
	public:
		void Allocate(size_t size);
		void Free();

		s32 GetEdgeIntersects(CPnt3D* firstPoint, CPnt3D* secondPoint, CPnt3D* edge) const;
		s32 GetEdgeIntersectsY(CPnt3D* firstPoint, CPnt3D* secondPoint) const;
	private:
		DI_PARAMS DI_PARAMS;
		CPnt4D* m_pts;
	};

	struct IntersectStruct
	{
		CPnt3D m_pos;
		CPnt3D m_norm;
		CNode* m_node;
	};

	struct DiIntersect
	{
		s32 m_Type;

		bool m_IntersectCharacters;
		bool m_AltitudeCharacters;
		bool m_ProximityCharacters;

		s32 m_Unused;

		CPnt3D m_Tail;
		CPnt3D m_Tip;
		CPnt3D m_MTail;
		CPnt3D m_MTip;

		s32 m_Cnt;
		s32 m_BufCnt;

		CNode* m_Node;
		CNode* m_TreeDoneNode;
		IntersectStruct* m_Intersects;
	};

	class CHit : public IntersectStruct
	{
	public:
		CPnt3D m_hit0;
		CPnt3D m_hit1;
	};
}