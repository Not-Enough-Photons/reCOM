#pragma once
#include <vector>
#include <string>

#include "placeholder.h"

#include "node_world.h"

#include "ai/ai_main.h"
#include "valve/valve_main.h"

#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath_main.h"
#include "gamez/zTexture/ztex_main.h"
#include "gamez/zWeapon/zwep_weapon.h"

namespace zdb
{
	class CNodeVector;
	class CNodeEx;
	class CSaveLoad;
	class CModel;
	class CAssetLib;

	const char* g_RootNodeTag = "ROOT";
	const char* g_DeletedNodeTag = "DELETED_NODE";

	class CNode
	{
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

		bool UpdateGrid() const;

		CNode* FindChild();

		undefined8 BuildMTW(const CMatrix& mat);

		virtual void Release();
		bool Rendered();

		void FreeAtom();
		undefined4 GetAtom();

		float GetRadius() const;
		float GetRadiusSq() const;

		undefined8 GetRotation() const;
		CPnt3D* GetScale(CPnt3D* scale) const;
		float GetScale() const;

		undefined4 GetSubMesh() const;

		void SetName(const char* name);
		void SetModelname(const char* name);
		bool SetActive(bool active);

		void SetPosition(float x, float y, float z);
		void SetScale(undefined8 param_2);

	public:
		const char* name;

	private:
		short refCount;
		int nodeType;
		int childCount;

		short stateFlags;
		short field82_0x9a;

		CNode* parent;
		std::vector<CNode*> children;
		CNodeVector nodeVector;
		
		CNodeEx* nodeEx;

		float posX;
		float posY;
		float posZ;

		float scaleX;
		float scaleY;
		float scaleZ;

		float radiusX;
		float radiusY;
		float radiusZ;
		float radiusMaxX;
		float radiusMaxY;
		float radiusMaxZ;
	};

	class CNodeVector
	{
	public:
		~CNodeVector();

		bool Exists(const CNode* node) const;
		bool Remove(const CNode* node);
		CNode* GetNode(const char* name) const;
	private:
		std::vector<CNode*> nodes;
		int size;
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

	class CModel : public CNodeEx
	{
	public:
		void Release(CNode* node);
	};

	class CCamera : public CNode
	{
	public:
		static void RegisterAnimCommands();
		float GetScaledRangeSquared(const CPnt3D& point);
	private:
		CPnt3D m_pos;
		float m_scaledrange;
	};

	class CAppCamera : public CCamera
	{
	public:
		static void RegisterAnimCommands();
	};

	class CLight : public CNode
	{
	private:
		float m_Red;
		float m_Green;
		float m_Blue;
		float m_Intensity;
		float m_Range;
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
	public:
		CSaveLoad();
		~CSaveLoad();

		CWorld* Load(const char* path);
		bool LoadAssetLib(CWorld* world, CAssetLib* library, int size);
		bool LoadAssetLib_PS2(CWorld* world, CAssetLib* library, int size);
		bool LoadPalettes_PS2(CAssetLib* library);
		bool LoadTextures_PS2(CAssetLib* library);
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
		DOOR,
		WINDOW,
		SWITCH,
		DEFUSE,
		MPBOMB,
		BREACH,
		UNKNOWN
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