#pragma once
#include <vector>
#include <string>

#include "placeholder.h"

#include "node_world.h"

#include "ai/ai_main.h"
#include "math/zmath_main.h"
#include "texture/ztex_main.h"
#include "valve/valve_main.h"
#include "zar/zar_main.h"

namespace zdb
{
	const char* g_RootNodeTag = "ROOT";
	const char* g_DeletedNodeTag = "DELETED_NODE";

	class CNode
	{
	public:
		CNode();
		~CNode();

		CNode* Create(const char* name);

		void AddChild(CNode* child);
		void DeleteChild(const CNode* child);
		void DeleteChildren();

		CNode* FindChild();

		undefined8 BuildMTW(const CMatrix& mat);

		virtual void Release();
		bool Rendered();

		void FreeAtom();
		undefined4 GetAtom();

		float GetRadius() const;
		float GetRadiusSq() const;

		undefined8 GetRotation() const;
		undefined8 GetScale() const;

		undefined4 GetSubMesh() const;

		void SetName(const char* name);
		void SetModelname(const char* name);

		void SetPosition(float x, float y, float z);
		void SetScale(undefined8 param_2);
	private:
		const char* name;
		short refCount;
		int nodeType;
		int size;

		CNode* parent;
		std::vector<CNode&> children;
	};

	class CNodeEx : public CNode
	{

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