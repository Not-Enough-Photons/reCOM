#pragma once
#include "gamez/zReader/zrdr_main.h"
#include "gamez/zNetwork/znet_main.h"
#include "gamez/zSystem/zsys_main.h"

class CMission;

static CMission theMission;

class CMission : CSaveModule
{
public:
	CMission() : CSaveModule("CMission", NULL) {}
	~CMission();

	static float nextFrameDelta;
public:
	void Init();

	void Open();
	void PreOpen();
	void Read(_zrdr* reader);
public:
	CZNetGame* netGame;
private:
	float weather_factor;
	int seal_command;
	float recycle_time;
	float recycle_range;
	float respawn_time;
	float respawn_fade;
	float satchel_timer;
};

class CZBombState
{
public:
	static int m_FutureBombState;
};