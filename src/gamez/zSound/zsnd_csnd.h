#pragma once
#include <vector>

#include "placeholder.h"

#include "valve\valve_main.h"
#include "zar\zar_main.h"

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
	CSnd();
	void SetupJukebox();
private:
	static bool m_isDisabled;
	static zar::CZAR* m_bnkArchive;
	static int m_bnkoffset;
	static std::vector<CSnd*> m_bankloaded;
	static std::vector<CSnd*> m_soundbank;

	float volume;
	char* field5_0x8;
	float range;
	float field7_0x10;
	void* bank;
	int curSndID;
	int field_0x1c;
	undefined4 field14_0x20;
	undefined4 field15_0x24;
	undefined4 field16_0x28;
	undefined field_0x1e;
	const char* subtitle;
	float subtitleTime;
	CValve* subtitleValve;
	int offset1;
	int offset2;
	bool oneshot;
	undefined field_0x40;
	int type;
};

class CSndInstance : public CSnd
{
public:
	static std::vector<CSnd*> m_sound_instance_pool;

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