#pragma once
#include <deque>

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

	struct vertex
	{
		CPnt3D pos;
		CPnt3D col;
		CPnt3D tcoords;
	};

	struct tag_VIS_PARAMS
	{
		// TODO:
		// Figure out the rest of the struct
		u32 m_parent_has_visuals : 1;
		u32 m_unused : 31;
		u32 m_field1;
		u32 m_field2;
		u32 m_field3;
		u32 m_field4;
		u32 m_field5;
	};

	struct tag_DETAIL_PARAMS
	{
		f32 m_range_sqd_to_camera;
	};

	class CVisBase
	{
	protected:
		void* m_data_buffer;
	};

	class CVisData
	{
	public:
		CVisData();
		~CVisData();

		void Clear();
		void NextVertex(u32 vertex);
		void SearchVertex();
		void SelectVertex(CVisual* vis, u32 vertex);
	};
	
	/// <summary>
	/// Representation of an object in 3D space, which will get passed to the rendering pipeline.
	/// </summary>
	class CVisual : public tag_VIS_PARAMS
	{
	public:
		enum LOD
		{
			LOW,
			MEDIUM,
			HIGH
		};
	public:
		static void AddLocalLight(CLight* light, CPnt3D* position);
		static void AlphaEnable(bool enableAlpha);
		static s32 ApplyDecal(u32 vertex, f32 opacity, CPnt3D* position, CMatrix* mat, CTexHandle* handle);
		static CVisual* Create(zar::CZAR& archive);
		static void Init();
		static void LandmarkEnable(bool enableLandmarks);
	public:
		bool Read(zar::CZAR& archive);
	public:
		static std::deque<CVisual*> m_stack_vid;

		static std::vector<CPnt3D*> m_lightMapList;
		static std::vector<CPnt3D*> m_shadowMapList;
		static std::vector<CPnt3D*> m_projectedMapList;

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

		static f32 m_opacity;
		
		u32 m_instance_cnt;
		void* m_detail_buff;
		u32 m_detail_cnt;
		size_t m_detail_size;
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

	class CVisualVector : public std::vector<CVisual*>
	{
	public:
		bool Exists(const CVisual* visual);
	};
}