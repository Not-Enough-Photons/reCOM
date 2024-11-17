#pragma once
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