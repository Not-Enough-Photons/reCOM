#pragma once
#include <vector>
#include <unordered_map>

#include <SDL3/SDL_audio.h>

#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zValve/zvalve.h"
#include "gamez/zSystem/zsys.h"

class CSnd;

enum SOUND_TYPE
{
	SND_NONE,
	SND_CONVERSATIONAL,
	SND_SITREP,
	SND_DEATH_DAMAGE,
	SND_NUM_TYPES
};

enum SOUND_MODE
{
	SND_MODE_UNKNOWN,
	SND_MODE_EFX,
	SND_MODE_MUSIC,
	SND_MODE_DIALOG,
	SND_MODE_BANK_DEFINED
};

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

extern bool vagArchiveIsOpen;
extern bool bnkArchiveIsOpen;
extern bool snd_system_initialized;
extern _zrdr* sound_rdr;
extern std::unordered_map<const char*, CSnd*> sound_map;
extern f32 vagLUT[5][2];

// From:
// https://github.com/eurotools/es-ps2-vag-tool/blob/main/PS2VagTool/Vag%20Functions/SonyVag.cs
enum class VAG_FLAGS
{
	VAG_NOTHING = 0,
	VAG_LOOP_LAST_BLOCK = 1,
	VAG_LOOP_REGION = 2,
	VAG_LOOP_END = 3,
	VAG_LOOP_FIRST_BLOCK = 4,
	VAG_UNK = 5,
	VAG_LOOP_START = 6,
	VAG_PLAYBACK_END = 7
};

struct tag_VAGHeader
{
	tag_VAGHeader();
	tag_VAGHeader(void* ptr, size_t size);
	
	char magic[4];
	s32 version;
	s32 unknown01;
	u32 samples;
	u32 rate;
	s32 unknown02;
	u32 unknown03;
	u32 unknown04;
	char name[16];
};

struct tag_VAGChunk
{
	s8 shift;
	s8 predict;
	u8 flags;
	u8* sample;
};

class CSnd
{
public:
	CSnd();

	static void Init();
	static void Close();
	static void UIOpen();
	static void AddNewCSnd(CSnd* sound);
	static CSnd* GetSoundByName(const char* name);
	static bool GetSubtitles();
	static bool vagReadOffset(const char* name, u32& offset, u32& size);
	static void LoadWAV(const char* name);
	static void LoadVAG(const char* name);
	
	void LoadCSnd(_zrdr* reader);
	float CalcVol(f32 volume, f32 masterVolume);
	void SetupJukebox();

	static SDL_AudioStream* m_audiostream;
	static u8* m_snd_data;
	static u32 m_snd_len;
	
	static s32 m_max_num_vags;

	static bool m_isDisabled;
	static bool m_bShowSubtitles;
	static bool m_hasreverb;
	static bool m_vagEnabled;
	static zar::CZAR m_vagArchive;
	static zar::CZAR m_bnkArchive;
	static s32 m_bnkoffset;
	static s32 m_vagoffset;

	static std::unordered_map<const char*, CSnd*> m_soundmap;
	static std::vector<CSnd*> m_bankloaded;
	static std::vector<CSnd*> m_soundbank;
	static std::vector<CSnd*> m_soundlist;
protected:
	f32 m_vol;

	char* m_name;

	PNT2D m_range;

	s32 m_bank;
	s32 m_ID;

	bool m_isStreamed;
	bool m_isOneShot;
	bool m_isHeadsetStream;

	u32 m_soundmode;
	u32 m_type;

	char* m_stream1name;
	char* m_stream2name;

	char* m_subtitle;
	CValve* m_subtitle_translator;
	f32 m_subtitle_time;

	s32 m_offset1;
	s32 m_offset2;
};

class CSndInstance : public CSnd
{
public:
	static f32 m_mastervol;
	static std::vector<CSnd*> m_sound_instance_pool;

	static void InitInstancePool(s32 count);
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
	static void Tick(f32 delta);
	static void Stop();

	static void Play(MUSIC_MODE mode, CSnd* sound);
	static void PlayRandom(MUSIC_MODE mode);
	
	static void NormalizeWeights();

	static bool IsInFight(bool inFight);
private:
	f32 m_weights;
	MUSIC_MODE m_currentmode;
	bool m_isinfight;
};

class CSndSequence
{
public:
	void CreateSequence(u32* param_1, s64 param_2);
	void Play();
	void Play(int** param_1);
	void Tick();
	void Stop();
};