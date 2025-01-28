#pragma once
#include <deque>

#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath.h"

class CShader;

namespace zar
{
	class CZAR;
}

namespace zdb
{
	class CNode;
	class CModel;

	class CVisBase;
	class CVisual;
	class CMesh;
	class CDecal;
	class CLight;
	class CTexHandle;

	class CCamera;
	class CLOD_band;
}

void hookupMesh(zar::CZAR* archive, zdb::CModel* model);
void hookupVisuals(zar::CZAR* archive, zdb::CModel* model);
void hookupVisuals(zar::CZAR* archive, zar::CKey* key, zdb::CNode* node, zdb::CModel* model, zdb::CVisBase* vis);

extern s32 node_index;

namespace zdb
{
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
		u32 m_field1 : 1;
		u32 m_unused : 30;
		CPnt4D m_field2;
	};

	struct tag_DETAIL_PARAMS
	{
		f32 m_range_sqd_to_camera;
	};

	class CVisBase
	{
	public:
		CVisBase(size_t size);
		
		static u32 m_instance_count;

		void* m_data_buffer;
		s32 m_buffer_count;
		size_t m_data_size;
		bool m_active;
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
		static void LandmarkEnable(bool enableLandmarks);
		
		void Init();

		bool Read(zar::CZAR& archive);

		void ApplyDecal(CDecal* decal);

		void SetBuffer();
		
		bool DrawLOD(CLOD_band* lod, f32 range, f32* distance);
		void Render();
		void VuUpdate(f32 opacity);

		u32 Release();

		static std::deque<CVisual*> m_stack_vid;

		static std::vector<CPnt3D*> m_lightMapList;
		static std::vector<CPnt3D*> m_shadowMapList;
		static std::vector<CPnt3D*> m_projectedMapList;

		static void* localLightBuf;
		static CLight* localLightPtr;

		static CPnt4D m_addColor;
		static CPnt4D m_basefog_color;
		static CPnt4D m_basefog_near;

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

		bool m_has_lods;
		
		u32 m_refcount;
		void* m_detail_buff;
		u32 m_detail_cnt;
		size_t m_detail_size;

		u32 m_instance_cnt;

		std::vector<CDecal*> m_decals;
		s32 m_decal_idx;

		s32 m_renderState;

		CShader* m_shader;

		u32 m_vbo;
		u32 m_vao;
	};

	class CMesh : public CVisual
	{
	public:
		u32 m_mtx_count;
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