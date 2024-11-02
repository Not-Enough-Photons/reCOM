#pragma once
#include "gamez/zReader/zrdr_main.h"

class CMission
{
public:
	static float nextFrameDelta;

	void Init();

	void Open();
	void PreOpen();
	void Read(_zrdr* reader);
private:
	float weather_factor;
	int seal_command;
	float recycle_time;
	float recycle_range;
	float respawn_time;
	float respawn_fade;
	float satchel_timer;
};