#pragma once
#include "gamez/zMath/zmath_main.h"
#include "gamez/zNode/node_main.h"

struct cam_wiggle
{
	float amplitude;
	float duration;
	float rate;
};

struct throw_params
{
	float m_abort_threshold;
	float max_distance_stand;
	float max_distance_crouch;
	float toss_power_threshold;
	float toss_aim_threshold;
};

class CCameraParams
{
public:
	CPnt3D m_cam_offset;
	CPnt3D m_cam_aimpoint;
};

namespace zdb
{
	class CCamera : public CNode
	{
	public:
		static void RegisterAnimCommands();

		static _zanim_cmd_hdr* CmdParseRelease(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseAcquire(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseIndoorsTest(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseSetRegions(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseGetRegions(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseParams(_zrdr* reader);

		static void CmdBeginParams(_zanim_cmd_hdr* header);

		static bool CmdTickControlSwitch(_zanim_cmd_hdr* header, float* delta);
		static bool CmdTickIndoorsTest(_zanim_cmd_hdr* header, float* delta);
		static bool CmdTickSetRegions(_zanim_cmd_hdr* header, float* delta);
		static bool CmdTickGetRegions(_zanim_cmd_hdr* header, float* delta);
		static bool CmdTickParams(_zanim_cmd_hdr* header, float* delta);
	public:
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
}