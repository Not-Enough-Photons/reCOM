#pragma once
#include "GameZ/zReader/zrdr_main.h"
#include "GameZ/zNetwork/znet_main.h"

void game_main(int argc, char** argv);
void process_arguments(int argc, char** argv);

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
public:
	void Start();
	void Exit();

	void SetMovie(const char* moviename);
	void UnInit();
private:
	bool m_movierunning;
	char* m_moviename;
	int m_savedFrameRate;
	int m_videoSave[2];
	float m_fadeTime;
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