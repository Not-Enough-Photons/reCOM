#pragma once
#include <vector>
#include <unordered_map>

#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath_main.h"
#include "gamez/zReader/zrdr_main.h"
#include "gamez/zValve/valve_main.h"

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

bool vagArchiveIsOpen = false;
bool bnkArchiveIsOpen = false;
_zrdr* sound_rdr;
bool snd_system_initialized = false;

std::unordered_map<const char*, CSnd*> sound_map;

class CSnd
{
public:
	CSnd();

	static void Init();
	static void AddNewCSnd(CSnd* sound);
	static CSnd* GetSoundByName(const char* name);
	static bool GetSubtitles();
public:
	void LoadCSnd(_zrdr* reader);
	float CalcVol(float volume, float masterVolume);
	void SetupJukebox();

	static bool m_isDisabled;
	static bool m_bShowSubtitles;
	static bool m_hasreverb;
	static zar::CZAR* m_vagArchive;
	static zar::CZAR* m_bnkArchive;
	static int m_bnkoffset;
	static int m_vagoffset;

	static std::unordered_map<const char*, CSnd*> m_soundmap;
	static std::vector<CSnd*> m_bankloaded;
	static std::vector<CSnd*> m_soundbank;
	static std::vector<CSnd*> m_soundlist;
protected:
	float m_vol;

	const char* m_name;

	PNT2D m_range;

	int m_bank;
	int m_ID;

	bool m_isStreamed;
	bool m_isOneShot;
	bool m_isHeadsetStream;

	unsigned int m_soundmode;
	unsigned int m_type;

	const char* m_stream1name;
	const char* m_stream2name;

	const char* m_subtitle;
	CValve* m_subtitle_translator;
	float m_subtitle_time;

	int m_offset1;
	int m_offset2;
};

class CSndInstance : public CSnd
{
public:
	static float m_mastervol;
	static std::vector<CSnd*> m_sound_instance_pool;

	static void InitInstancePool(int count);
};

class CSndJukebox
{
public:
	// Disallow construction of a static class
	CSndJukebox() = delete;
public:
	static void Cleanup();
	CRdrFile* LoadPlaylists();
	static void LoadMusicLists();

	static void Start();
	static void Tick(float delta);
	static void Stop();

	static void Play(MUSIC_MODE mode, CSnd* sound);
	static void PlayRandom(MUSIC_MODE mode);
	
	static void NormalizeWeights();

	static bool IsInFight(bool inFight);
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