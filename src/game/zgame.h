#pragma once
#include "reader/zrdr_main.h"
#include "network/znet_main.h"

class CMission;

static CMission theMission;

void game_main();

class CGame
{
public:
	static bool StartEngine();
	static void StartPlay();
	static void Tick();
};

class COurGame : public CGame
{
public:
	static bool StartEngine();
};

class CMission
{
public:
	void Init();

	void Open();
	void PreOpen();
	void Read(zrdr* reader);
private:
	float weather_factor;
	int seal_command;
	float recycle_time;
	float recycle_range;
	float respawn_time;
	float respawn_fade;
	float satchel_timer;
};

class CGameState
{
public:
	virtual void Start();
	virtual void Exit();
};

class CMenuState : public CGameState
{
	void Start();
	void Exit();
};

class CCinematicState : public CGameState
{
	void Start();
	void Exit();
};

class CCoreState : public CGameState
{
	void Start();
	void Exit();
};

class CExitState : public CGameState
{
	void Start();
	void Exit();
};

class CMPExitState : public CGameState
{
	void Start();
	void Exit();
};

class CRebootState : public CGameState
{
	void Start();
	void Exit();
};

class CShutdownState : public CGameState
{
	void Start();
	void Exit();
};

class CGameStateChangeCmd
{
public:
	static void CreatePool(int size);
};