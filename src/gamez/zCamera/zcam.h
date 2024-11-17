#pragma once
#include "gamez/zMath/zmath_main.h"

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