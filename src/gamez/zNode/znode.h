#pragma once
#include <vector>
#include <string>

#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zRender/vis/zvis.h"
#include "gamez/zTexture/ztex.h"
#include "gamez/zValve/zvalve.h"
#include "gamez/zSystem/zsys.h"

namespace zdb
{
	class tag_NODE_PARAMS;
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

	extern CNodeUniverse* NodeUniverse;
	extern CWorld* theWorld;

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
		CNode* Create(const char* name);

		void AddChild(CNode* child);
		int DeleteChild(CNode* child);
		void DeleteChildren();
		void RemoveFromParent();

		bool UpdateGrid() const { return false; }

		CNode* FindChild(CNode* child, bool nested);
		CNode* FindChild(const char* child, bool nested);

		CMatrix& BuildMTW(CMatrix& mat);

		virtual short Release();
		bool Rendered();

		void InsertAtom(CGridAtom* atom);
		CGridAtom* GetAtom(int index);
		void FreeAtom();

		float GetRadius() const;
		float GetRadiusSq() const;

		CPnt3D* GetRotation(const CPnt3D* rotation) const;
		CPnt3D* GetScale(CPnt3D* scale) const;
		float GetScale() const;

		CSubMesh* GetSubMesh() const;

		void SetName(const char* name);
		void SetModel(CModel* model);
		void SetModelname(const char* name);
		bool SetActive(bool active);

		void SetPosition(float x, float y, float z);
		void SetRotation(const CQuat& rotation) {};
		void SetScale(float scaleFactor);
		void SetScale(CPnt3D* scale);
	public:
		const char* m_name;
	protected:
		CNode* m_parent;
		CNodeVector m_child;
		// TODO:
		// Implement the CDIVector class and CDI
		// CDIVector m_di;
		// TODO:
		// Implement the CVisualVector class
		// CVisualVector m_visual;

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
		const char* m_modelname;
		u32 m_region_mask;
	};

	class CNodeUniverse : public std::vector<CNode*>
	{
	public:
		bool AddNode(CNode* node);
		void RemoveNode(CNode* node);
		CNode* GetElement(int index) const;
		int GetIndex(CNode* node) const;
	private:
		bool m_locked;
	};

	class CWorld : public CNode
	{
		friend class CCamera;
	public:
		CWorld() : CNode() {}
		~CWorld();

		static CWorld* m_world;

		static float m_scale;
		static float m_invscale;

		static int GetVersion();
		static void Init();
	public:
		void Uninit();
		void diTick();
		void Update();

		void AddChild(CNode* child);
		void AddLandmark(CNode* landmark);
		void AddTextureAssetCharacter(const CNode& textureAsset);
		void ReserveChildren(int count);

		void DeleteChildren();
		void DeleteLandmark(const CNode& landmark);

		// undefined4 DismemberWorldModel();

		void ClearLightMapList();
		void ClearShadowList();
		void WipeoutTextureAssetCharacters();

		void ComputeLightIntensity(float intensity, const CPnt3D& point, float* lightRef);

		void GetTexHandle() const;
		// undefined4 GetTextureByName(const char* name) const;
		int GetModel() const;
	private:
		CCamera* m_camera;

		u32 m_default_soiltype;
		char* m_default_soiltype_name;

		s32 m_maxOverlap;

		CGrid* m_grid;
		CNodeVector m_landmarks;
		u32 m_numNoFarClipNodes;
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
		void Read(CSaveLoad& saver);
		void Release(CNode* node);
	private:
		s32 m_variant;
		bool m_bForceExport;
		bool m_bbox_valid;
		// CRefList m_list;
		CAssetLib* m_AssetLib;
	};

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
		~CSaveLoad();

		CWorld* Load(const char* path);
		bool LoadAssetLib(CWorld* world, CAssetLib* library, int size);
		bool LoadAssetLib_PS2(CWorld* world, CAssetLib* library, int size);
		bool LoadPalettes_PS2(CAssetLib* library);
		bool LoadTextures_PS2(CAssetLib* library);
	private:
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
	CNodeAction* GetActionById(int id) const;
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