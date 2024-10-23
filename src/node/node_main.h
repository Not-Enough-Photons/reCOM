#pragma once
#include <vector>
#include <string>

#include "placeholder.h"

#include "math/zmath_main.h"
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

	class CNodeAction : public CNodeEx
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