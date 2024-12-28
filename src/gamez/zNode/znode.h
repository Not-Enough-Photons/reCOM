#pragma once
#include <vector>
#include <string>

#include "node_world.h"

#include "gamez/zAI/zai.h"
#include "gamez/zAnim/zanim.h"
#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zTexture/ztex.h"
#include "gamez/zSeal/zseal.h"
#include "gamez/zValve/zvalve.h"
#include "gamez/zWeapon/zwep_weapon.h"

namespace zdb
{
	class tag_NODE_PARAMS;
	class CNodeVector;
	class CNodeEx;
	class CSaveLoad;
	class CModel;
	class CAssetLib;
	class CGridAtom;

	const char* g_RootNodeTag = "ROOT";
	const char* g_DeletedNodeTag = "DELETED_NODE";

	struct tag_NODE_PARAMS
	{
		CMatrix m_matrix;
		CBBox m_bbox;
		char m_type;
		bool m_active : 1;
		bool m_dynamic_motion : 1;
		bool m_dynamic_light : 1;
		bool m_landmark : 1;
		bool m_light : 1;
		bool m_prelight : 1;
		bool m_fog : 1;
		bool m_transparent : 1;
		// imposters/billboards
		int m_facade : 2;
		bool m_reflective : 1;
		bool m_bumpmap : 1;
		bool m_hasDI : 1;
		int m_region_shift : 5;
		bool m_has_visuals_prior_to_export : 1;
		bool m_shadow : 1;
		bool m_worldchild : 1;
		bool m_char_common : 1;
		bool m_NOTUSED : 1;
		bool m_hasVisuals : 1;
		bool m_hasMesh : 1;
		bool m_scrolling_texture : 1;
		bool m_light_dynamic : 1;
		bool m_light_static : 1;
		bool m_clutter : 1;
		bool m_mtx_is_identity : 1;
		bool m_use_parent_bbox : 1;
		bool m_apply_clip : 1;
	};

	class CNode : public tag_NODE_PARAMS
	{
		friend class CNodeVector;
	public:
		CNode();
		~CNode();

		static CNode* CreateInstance(CSaveLoad& save);
		static CNode* CreateInstance(const char* name, const CPnt3D& position, const CPnt3D& rotation);
		static CNode* CreateInstance(CModel* model, const CPnt3D& position, const CPnt3D& rotation);
	public:
		CNode* Create(const char* name);

		void AddChild(CNode* child);
		int DeleteChild(CNode* child);
		void DeleteChildren();
		void RemoveFromParent();

		bool UpdateGrid() const;

		CNode* FindChild(CNode* child, bool isCell);
		CNode* FindChild(const char* child, bool isCell);

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
		void SetModelname(const char* name);
		bool SetActive(bool active);

		void SetPosition(float x, float y, float z);
		void SetRotation(const CQuat& rotation);
		void SetScale(float scaleFactor);
		void SetScale(CPnt3D* scale);

	protected:
		CNode* m_parent;
		CNodeVector m_child;
		// TODO:
		// Implement the CDIVector class and CDI
		// CDIVector m_di;
		// TODO:
		// Implement the CVisualVector class
		// CVisualVector m_visual;

		const char* m_name;
		CNodeEx* m_nodeEx;
		char m_customGlobalLight;
		bool m_frameRendered;
		bool m_flatten;
		bool m_modified;
		bool m_character;
		bool m_character_infov;
		int m_unused;
		float m_Opacity;
		CGridAtom** m_Atom;
		int m_TickNum;
		short m_AtomCnt;
		short m_AtomAlloc;
		short m_count;
		short m_vid;
		CModel* m_model;
		const char* m_modelname;
		unsigned int m_region_mask;
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

	class CNodeVector : public std::vector<CNode*>
	{
	public:
		bool Exists(const CNode* node) const;
		bool Remove(const CNode* node);
		CNode* GetNode(const char* name) const;
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
		virtual void* OnWeaponHit(CNode* node, IntersectStruct* intersection, CZProjectile* projectile) = 0;
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
		int m_variant;
		bool m_bForceExport;
		bool m_bbox_valid;
		// CRefList m_list;
		CAssetLib* m_AssetLib;
	};

	class CLight : public CNode
	{
	private:
		float m_maxRangeSq;
		float m_maxRange;
		float m_minRange;
		float m_invMaxRange;
		float m_invDeltaRange;
		float m_opacity;
		CPnt3D m_diffuse;
		bool m_appliedToNode;
		CPnt3D m_WorldPosition;
	};

	class CVisual
	{
	public:
		CVisual();
		~CVisual();

		static CVisual* Create(zar::CZAR* archive);
	};

	class CMesh : public CVisual
	{

	};

	class CSubMesh : public CMesh
	{

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
		int m_version;
	};

	class CAssetLib
	{

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

	CNodeAction(zdb::CNode* node, CZAnim* animToPlay, CValve* actionValve, zdb::CTexHandle* handle);
	~CNodeAction();

	static void Open(zdb::CWorld* world, const char* readerName);
	static void Close();

	CNodeAction* FindActionByValve(const CValve* valve) const;
	CNodeAction* GetAction(bool isBase) const;
	CNodeAction* GetActionById(int id) const;
	const char* GetActionType(ACTION_TYPE type) const;
	CNodeAction* GetClosestAction(const CPnt3D* position, float radius) const;

	bool ExecuteAction(CZSealBody* seal, unsigned int actionFlags) const;

	template<class T>
	bool OnAction(zdb::CNode* node, T* type) const;
private:
	static std::vector<CNodeAction> m_actions;

	CNodeAction** actionList;

	zdb::CNode* node;
	CZAnim** animations;
	std::vector<CZAnim*> animVector;
	CZAnim* actionAnimation;
	CValve* actionValve;
	zdb::CTexHandle* iconBitmapHandle;

	int typeFlag;
	unsigned int actionFlags;
};