#pragma once
#include "gamez/zNode/znode.h"
#include "gamez/zMath/zmath.h"

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
	struct DI_PARAMS
	{
		CPnt4D m_nrm;

		int m_region;
		int m_refcount;

		char m_ditype;
		int m_ptcount;
		int m_material;

		char m_cameratype;

		char m_appflags;

		bool m_inside;
		bool m_shadow;

		int m_reserved;
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

		int GetEdgeIntersects(CPnt3D* firstPoint, CPnt3D* secondPoint, CPnt3D* edge) const;
		int GetEdgeIntersectsY(CPnt3D* firstPoint, CPnt3D* secondPoint) const;
	private:
		DI_PARAMS DI_PARAMS;
		CPnt4D* m_pts;
	};

	struct DiIntersect
	{
		int m_Type;

		bool m_IntersectCharacters;
		bool m_AltitudeCharacters;
		bool m_ProximityCharacters;

		int m_Unused;

		CPnt3D m_Tail;
		CPnt3D m_Tip;
		CPnt3D m_MTail;
		CPnt3D m_MTip;

		int m_Cnt;
		int m_BufCnt;
		
		CNode* m_Node;
		CNode* m_TreeDoneNode;
		IntersectStruct* m_Intersects;
	};

	struct IntersectStruct
	{
		CPnt3D m_pos;
		CPnt3D m_norm;
		CNode* m_node;
	};

	class CHit : public IntersectStruct
	{
	public:
		CPnt3D m_hit0;
		CPnt3D m_hit1;
	};
}