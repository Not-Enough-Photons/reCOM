#pragma once
#include "placeholder.h"

enum MUSIC_MODE
{
	MODE_0,
	MODE_1,
	MODE_2,
	MODE_3,
	MODE_4,
	MODE_5,
	MODE_6,
	MODE_7,
	MODE_8,
	MODE_9
};

class CSnd
{
public:
	void SetupJukebox();

private:
	bool m_isDisabled;
};

class CSndInstance : CSnd
{
public:
	static void InitInstancePool(int count);
};

class CSndJukebox
{
public:
	void Cleanup();
	void LoadPlaylists();
	void LoadMusicLists();

	void Start();
	void Tick(MUSIC_MODE mode);
	void Stop();

	void Play(MUSIC_MODE mode, undefined8 param_2);
	void PlayRandom();
	
	void NormalizeWeights();

	bool IsInFight(bool inFight);
private:
	float m_weights;
	MUSIC_MODE m_currentmode;
	bool m_isinfight;
};

class CSndSequence
{
public:
	void CreateSequence(unsigned int* param_1, long param_2);
	void Play();
	void Play(int** param_1);
	void Tick();
	void Stop();
};