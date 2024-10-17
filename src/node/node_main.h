#pragma once
#include <vector>
#include <string>

#include "placeholder.h"
#include "math/zmath_main.h"

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

		void AddChild(const CNode& child);
		void DeleteChild(const CNode& child);
		void DeleteChildren();

		CNode* FindChild();

		undefined8 BuildMTW(const CMatrix& mat);

		void Release();
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
		const char* m_name;
	};

	class CNodeEx : public CNode
	{

	};

	class CNodeAction : public CNodeEx
	{

	};

	class CModel : public CNodeEx
	{

	};

	class CCamera : public CNode
	{
	public:
		static void RegisterAnimCommands();

		// i'm not sure why the names are capitalized
		// feels like i'm being yelled at
		static float FOV;
		static float CLIP;
		static bool CLIP_ALL;
		static float FOG_RANGE;
		static float FOG_ALTITUDE;
		static float LOD_MULTIPLIER;
		static bool ON;
		static void DYNAMICS_RELEASE_CAMERA();
		static void DYNAMICS_ACQUIRE_CAMERA();
		static bool CAMERA_INDOORS;
		static void SET_CAMERA_REGION_TEST(bool test);
		static bool GET_CAMERA_REGION_TEST();
		static void CAMERA_3RD_PERSON();
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
}