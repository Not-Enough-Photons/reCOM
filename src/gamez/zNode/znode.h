#pragma once
#include <vector>
#include <string>

#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zRender/zVisual/zvis.h"
#include "gamez/zValve/zvalve.h"
#include "gamez/zSystem/zsys.h"

/// -------------------------------------------
/// FORWARD DECLARATIONS
/// -------------------------------------------
class CLOD_Object;
class CMaterial_Object;

namespace zdb
{
	struct tag_NODE_PARAMS;
	class CNode;
	class CNodeEx;

	class CGridAtom;
	class CCell;
	class COrderedCell;

	class CSaveLoad;
	class CModel;
	class CAssetLib;

	class CNodeUniverse;
	class CWorld;
	class CAppCamera;
	class CGrid;

	class CVisual;
	class CMesh;
	class CSubMesh;

	class CTexture;
	class CTexHandle;

	class CAssetLib;
}

namespace zdb
{
	extern u32 numNodes;

	extern CNodeUniverse* NodeUniverse;
	extern CWorld* theWorld;

	struct _globalLight
	{
		CPnt4D dir[3];
		CPnt4D col[3];
		CPnt4D ambient;
	};

	struct tag_NODE_PARAMS
	{
		CMatrix m_matrix;
		CBBox m_bbox;
		u32 m_type;
		u32 m_active : 1;
		u32 m_dynamic_motion : 1;
		u32 m_dynamic_light : 1;
		u32 m_landmark : 1;
		u32 m_light : 1;
		u32 m_prelight : 1;
		u32 m_fog : 1;
		u32 m_transparent : 1;
		u32 m_facade : 2;
		u32 m_reflective : 1;
		u32 m_bumpmap : 1;
		u32 m_hasDI : 1;
		u32 m_region_shift : 5;
		u32 m_has_visuals_prior_to_export : 1;
		u32 m_shadow : 1;
		u32 m_worldchild : 1;
		u32 m_char_common : 1;
		u32 m_NOTUSED : 1;
		u32 m_hasVisuals : 1;
		u32 m_hasMesh : 1;
		u32 m_scrolling_texture : 1;
		u32 m_light_dynamic : 1;
		u32 m_light_static : 1;
		u32 m_clutter : 1;
		u32 m_mtx_is_identity : 1;
		u32 m_use_parent_bbox : 1;
		u32 m_apply_clip : 1;
	};

	struct tag_GRID_PARAMS
	{
		struct tag_SIZE
		{
			s32 cx;
			s32 cy;
		};

		s32 m_AtomCnt;
		s32 m_posts;
		f32 m_CellDim;
		tag_SIZE m_CellCount;
	};

	class CNodeVector : public std::vector<CNode*>
	{
	public:
		bool Exists(const CNode* node) const;
		bool Remove(const CNode* node);
		CNode* GetNode(const char* name) const;
	};

	class CNode : public tag_NODE_PARAMS
	{
		friend class CNodeVector;
		friend class CWorld;
	public:
		CNode();

		static CNode* CreateInstance(CSaveLoad& save);
		static CNode* CreateInstance(const char* name, const CPnt3D& position, const CPnt3D& rotation);
		static CNode* CreateInstance(CModel* model, const CPnt3D& position, const CPnt3D& rotation);
	public:
		void InitNodeParams(tag_NODE_PARAMS* other = NULL);
		virtual bool Read(CSaveLoad& sload);

		CNode* Create(const char* name);

		void AddChild(CNode* child);
		s32 DeleteChild(CNode* child);
		void DeleteChildren();
		void RemoveFromParent();

		bool UpdateGrid() const { return false; }

		CNode* FindChild(CNode* child, bool nested);
		CNode* FindChild(const char* child, bool nested);

		CMatrix& BuildMTW(CMatrix& mat);

		void ReserveChildren(size_t size);
		void ReserveDI(size_t size);
		void ReserveVisuals(size_t size);

		bool AddVisual(CVisual* visual);
		void SetParentHasVisuals();

		virtual s16 Release();
		bool Rendered();

		void InsertAtom(CGridAtom* atom);
		CGridAtom* GetAtom(s32 index);
		void FreeAtom();

		f32 GetRadius() const;
		f32 GetRadiusSq() const;

		CPnt3D* GetRotation(const CPnt3D* rotation) const;
		CPnt3D* GetScale(CPnt3D* scale) const;
		f32 GetScale() const;

		CSubMesh* GetSubMesh() const;

		void SetName(const char* name);
		void SetModel(CModel* model);
		void SetModelname(const char* name);
		bool SetActive(bool active);

		void SetPosition(f32 x, f32 y, f32 z);
		void SetRotation(const CQuat& rotation) {};
		void SetScale(f32 scaleFactor);
		void SetScale(CPnt3D* scale);
	public:
		char* m_name;
	protected:
		CNode* m_parent;
		CNodeVector m_child;
		// TODO:
		// Implement the CDIVector class and CDI
		// CDIVector m_di;
		// TODO:
		// Implement the CVisualVector class
		CVisualVector m_visual;

		CNodeEx* m_nodeEx;
		bool m_customGlobalLight;
		bool m_frameRendered;
		bool m_flatten;
		bool m_modified;
		bool m_character;
		bool m_character_infov;
		s32 m_unused;
		f32 m_Opacity;
		CGridAtom** m_Atom;
		s32 m_TickNum;
		s16 m_AtomCnt;
		s16 m_AtomAlloc;
		s16 m_count;
		s16 m_vid;
		CModel* m_model;
		char* m_modelname;
		u32 m_region_mask;
	};

	class CNodeUniverse : public std::vector<CNode*>
	{
	public:
		bool AddNode(CNode* node);
		void RemoveNode(CNode* node);
		CNode* GetElement(s32 index) const;
		s32 GetIndex(CNode* node) const;
	public:
		bool m_locked;
	};

	class CWorld : public CNode
	{
		friend class CCamera;
	public:
		CWorld() : CNode() {}
		~CWorld();

		static CCamera* m_camera;
		static CWorld* m_world;

		static f32 m_scale;
		static f32 m_invscale;

		static s32 GetVersion();
	public:
		void Init() {}
		void Uninit() {}

		void diTick();
		void Update();

		s32 Initalize();

		void AddChild(CNode* child);
		void AddLandmark(CNode* landmark);
		void AddTextureAssetCharacter(const CNode& textureAsset);
		void ReserveChildren(s32 count);

		void DeleteChildren();
		void DeleteLandmark(const CNode& landmark);

		// undefined4 DismemberWorldModel();

		void ClearLightMapList();
		void ClearShadowList();
		void WipeoutTextureAssetCharacters();

		void ComputeLightIntensity(f32 intensity, const CPnt3D& point, f32* lightRef);

		void GetTexHandle() const;
		// undefined4 GetTextureByName(const char* name) const;
		int GetModel() const;
	private:
		u32 m_default_soiltype;
		char* m_default_soiltype_name;

		s32 m_maxOverlap;

		// TODO:
		// implement these two container types
		// CRenderMapVector m_shadows;
		// CLightMapVector m_lightMaps;

		// CLOD_Object m_LOD_Object;
		// CMaterial_Object m_Material_Object;
		// CSubSurf_Object m_SubSurf_Object;
		// CPreLight_Object m_PreLight_Object;
		// CProjectedMap_Object m_ProjectedMap_Object;
		// CScrollingTexture_Object m_ScrollingTexture_Object;

		bool m_night_mission;

		CPnt3D m_lensfx_nvg;
		CPnt3D m_lensfx_starlightscope;

		_globalLight m_gLight;

		bool m_gLightDirUpdate;
		bool m_gLightColUpdate;
		CPnt3D m_shadow_vector;

		CGrid* m_grid;
		CNodeVector m_landmarks;
		u32 m_numNoFarClipNodes;

		// TODO:
		// implement this type
		// CTextureAssetCharacterList m_TextureAssetCharacters;
		// CTexList m_TextureCharacterCommon;
		// CTexList m_TextureDecals;
		CTexture* m_shadowTex[4];
		CTexHandle* m_shadowTexH;
	};

	/// <summary>
	/// Doubly linked list of atoms that occupy a single cell.
	/// </summary>
	class CGridAtom
	{
	public:
		CNode* Ent;
		CGridAtom* Next;
		CGridAtom* Prev;
	};

	class CCell
	{
	public:
		struct GRIDCELLATOM
		{
			CGridAtom* cellAtom;
			s32 ring;
			s32 x;
			s32 z;
		};
	};

	class COrderedCell
	{
	private:
		s32 m_gridCellAtomCnt;
		s32 m_rt_gridCellAtomCnt;
		s32 m_viewX;
		s32 m_viewZ;
	};

	class CGrid : tag_GRID_PARAMS
	{
	public:
		CGrid();
		~CGrid();
	public:
		void Insert(CNode* node);
	private:
		CFRect m_extents;
		CWorld* m_world;

		bool m_ClutterCreated;

		CGridAtom** m_Atoms;
		CGridAtom** m_AtomBuf;
		CGridAtom** m_FreeAtoms;
		s32 m_AtomFreeCnt;
		s32 m_AtomFreePtr;

		f32 m_InvCellDim;
		f32 m_GridCellToI;
		f32 m_ClutterToI;
		s32 m_TickNum;

		bool m_LineWalk;
		u8 m_RowCellIn;
		u8 m_CurCellOut;

		CPnt3D m_Pnts[5];
		CPnt3D m_Edge[5];

		s32 m_PntCnt;

		s32 m_ix;
		s32 m_ixb;

		s32 m_xx;
		s32 m_iz;

		s32 m_izb;
		s32 m_zz;
		s32 m_iz_start;
		s32 m_iz_next_row;
		s32 m_iz_dir;
		CGridAtom* m_NextAtom;
		
		CPnt3D m_origin;
		s32 m_ring;

		COrderedCell m_orderedCells;
	};

	class CWind
	{
	public:
		static void RegisterAnimCommands();
		void CmdParseWind();
	};

	class CNodeEx : public CNode
	{
	public:
		virtual void OnAction(CNode* node, void* action) = 0;
		virtual void OnCopy(CNode* node, CNode* other) = 0;
		virtual void OnDelete(CNode* node) = 0;
		virtual void OnDoubleClick(CNode* node) = 0;
		virtual void OnMove(CNode* node) = 0;
		virtual void OnSelect(CNode* node, bool selected) = 0;
		// virtual void* OnWeaponHit(CNode* node, IntersectStruct* intersection, CZProjectile* projectile) = 0;
	};

	class CModel : public CNode
	{
	public:
		CModel(const char* name);
		~CModel();

		static CModel* Create(CSaveLoad& saver, CAssetLib* library);
	public:
		bool Read(CSaveLoad& sload);
		void Release(CNode* node);
	private:
		s32 m_variant;
		bool m_bForceExport;
		bool m_bbox_valid;
		// CRefList m_list;
		CAssetLib* m_AssetLib;
	};

	class CModelVector : public std::vector<CModel*> {};

	class CLight : public CNode
	{
	private:
		f32 m_maxRangeSq;
		f32 m_maxRange;
		f32 m_minRange;
		f32 m_invMaxRange;
		f32 m_invDeltaRange;
		f32 m_opacity;
		CPnt3D m_diffuse;
		bool m_appliedToNode;
		CPnt3D m_WorldPosition;
	};

	class CSaveLoad
	{
		friend class CNode;
	public:
		CSaveLoad();

		CWorld* Load(const char* path);
		bool LoadAssetLib(CWorld* world, CAssetLib* library, size_t size);
		bool LoadAssetLib_PS2(CWorld* world, CAssetLib* library, size_t size);
		bool LoadPalettes_PS2(CAssetLib* library);
		bool LoadTextures_PS2(CAssetLib* library);
	public:
		CWorld* m_world;
		zar::CZAR m_zfile;
		char m_zed_filename[1024];
		s32 m_version;
	};
}

class CNodeAction : public zdb::CNodeEx
{
public:
	enum ACTION_TYPE
	{
		ACT_DOOR,
		ACT_WINDOW,
		ACT_SWITCH,
		ACT_DEFUSE,
		ACT_MPBOMB,
		ACT_BREACH,
		ACT_SATCHEL_CHARGE,
		ACT_UNKNOWN
	};

	// CNodeAction(zdb::CNode* node, CZAnim* animToPlay, CValve* actionValve, zdb::CTexHandle* handle);
	// ~CNodeAction();

	static void Open(zdb::CWorld* world, const char* readerName);
	static void Close();

	// CNodeAction* FindActionByValve(const CValve* valve) const;
	CNodeAction* GetAction(bool isBase) const;
	CNodeAction* GetActionById(s32 id) const;
	const char* GetActionType(ACTION_TYPE type) const;
	CNodeAction* GetClosestAction(const CPnt3D* position, float radius) const;

	// bool ExecuteAction(CZSealBody* seal, unsigned int actionFlags) const;

	template<class T>
	bool OnAction(zdb::CNode* node, T* type) const;
private:
	static std::vector<CNodeAction> m_actions;

	CNodeAction** actionList;

	zdb::CNode* node;
	// CZAnim** animations;
	// std::vector<CZAnim*> animVector;
	// CZAnim* actionAnimation;
	CValve* m_valve;
	zdb::CTexHandle* m_actionBitmap;

	s32 m_type;
	u32 m_flags;
};