#pragma once
#include <vector>
#include <string>

namespace zdb
{
	class CNode
	{
	public:
		CNode();
		CNode(int id, std::string name);
		CNode(int id, std::string name, const CNode& parent);

		CNode(const CNode& other);

		~CNode();

		int GetNodeID() const;
		std::string GetNodeName() const;
		CNode& GetParent() const;
		CNode&& GetChildren() const;
	private:
		int m_NodeID;
		std::string m_NodeName;
		CNode* m_Parent;
		CNode** m_Children;
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