#pragma once
#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath.h"

namespace zdb
{
	class CVisual;
	class CMesh;
	class CLight;
	class CTexHandle;

	class CCamera;

	enum tag_ZVIS_FOV
	{
		ZVIS_FOV_CLIP,
		ZVIS_FOV_ALL_IN,
		ZVIS_FOV_ALL_OUT,
		ZVIS_FOV_NUM
	};

	class CVisBase
	{
	public:
		CVisBase();
		~CVisBase();
	};

	class CVisData
	{
		CVisData();
		~CVisData();

		void Clear();
		void NextVertex(unsigned int vertex);
		void SearchVertex();
		void SelectVertex(CVisual* vis, unsigned int vertex);
	};

	class CVisual : public CVisBase
	{
	public:
		static void* localLightBuf;
		static CLight* localLightPtr;

		static PNT3D m_addColor;
		static PNT3D m_basefog_color;

		static bool m_applyDetailTexture;
		static bool m_applyLocalLights;
		static bool m_applyMultipass;
		static bool m_applyShadow;
		static bool m_fogEnable;
		static bool m_lightingEnable;

		static CMatrix m_modelToWorld;
		static CMatrix m_WorldToModel;

		static CCamera* m_camera;
		static s32 custom;

		static float m_opacity;

		static void AddLocalLight(CLight* light, CPnt3D* position);
		static void AlphaEnable(bool enableAlpha);
		static int ApplyDecal(unsigned int vertex, float opacity, CPnt3D* position, CMatrix* mat, CTexHandle* handle);
		static CMesh* Create(zar::CZAR& archive);
		static void Init();
		static void LandmarkEnable(bool enableLandmarks);
	protected:

	};

	class CMesh : public CVisual
	{

	};

	class CSubMesh : public CMesh
	{

	};

	class CDecal : public CVisual
	{

	};
}