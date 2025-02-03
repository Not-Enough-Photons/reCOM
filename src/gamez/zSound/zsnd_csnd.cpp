#include "zsnd.h"

#include "gamez/zArchive/zar.h"
#include "gamez/zFTS/zfts.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zSystem/zsys.h"

s32 g_iReverbTime = 0;

bool vagArchiveIsOpen = false;
bool bnkArchiveIsOpen = false;
bool snd_system_initialized = false;

zar::CZAR CSnd::m_bnkArchive;
zar::CZAR CSnd::m_vagArchive;

SDL_AudioStream* CSnd::m_audiostream = NULL;
u8* CSnd::m_snd_data = NULL;
u32 CSnd::m_snd_len = 0;

s32 CSnd::m_max_num_vags = 0;
bool CSnd::m_isDisabled = false;
bool CSnd::m_bShowSubtitles = false;
bool CSnd::m_vagEnabled = false;
std::vector<CSnd*> CSnd::m_soundlist;
std::unordered_map<const char*, CSnd*> CSnd::m_soundmap;

_zrdr* sound_rdr = NULL;

s16* vagDecode(u8* ptr, tag_VAGHeader& header);

CSnd::CSnd()
{
	if (!m_isDisabled)
	{
		
	}
}

void CSnd::Init()
{
	if (m_isDisabled)
	{
		return;
	}

	if (!vagArchiveIsOpen)
	{
		vagArchiveIsOpen = true;
		m_vagArchive.Open("D:/RUN/SOUNDS/VAGSTORE.ZAR", 0, 33, 16);
	}
}

void CSnd::UIOpen()
{
	if (sound_rdr == NULL)
	{
		sound_rdr = zrdr_read("sounds.rdr", NULL, 0);
	}

	if (m_vagEnabled)
	{
		m_max_num_vags = 4;
	}
}

void CSnd::Close()
{
	m_max_num_vags = 0;
	Headset::ftsDeleteHeadset();
}

bool CSnd::vagReadOffset(const char* name, u32& offset, u32& size)
{
	if (m_isDisabled)
	{
		return false;
	}

	zar::CKey* key = m_vagArchive.FindKey(name);
	
	if (key)
	{
		offset = key->GetOffset();
		size = key->GetSize();
		m_vagArchive.CloseKey(key);
		return true;
	}
	
	return false;
}

void CSnd::LoadWAV(const char* name)
{
	SDL_PauseAudioStreamDevice(m_audiostream);
	m_snd_data = NULL;
	m_snd_len = 0;
	
	zar::CKey* key = m_vagArchive.OpenKey(name);

	if (!key)
	{
		return;
	}
    
	void* buffer = zmalloc(key->GetSize());
	m_vagArchive.Fetch(key, buffer, key->GetSize());
    
	SDL_IOStream* stream = SDL_IOFromMem(buffer, key->GetSize());
    
	m_snd_data = NULL;
	m_snd_len = NULL;
	SDL_AudioSpec audioSpec { SDL_AUDIO_S16, 1, 11025 };
	m_audiostream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec, NULL, NULL);
	SDL_LoadWAV_IO(stream, false, &audioSpec, &m_snd_data, &m_snd_len);

	SDL_ResumeAudioStreamDevice(m_audiostream);

	if (SDL_GetAudioStreamAvailable(m_audiostream) < (s32)m_snd_len)
	{
		SDL_PutAudioStreamData(m_audiostream, m_snd_data, m_snd_len);
	}
	
	m_vagArchive.CloseKey(key);
}

void CSnd::LoadVAG(const char* name)
{
	SDL_PauseAudioStreamDevice(m_audiostream);
	m_snd_data = NULL;
	m_snd_len = 0;
	
	zar::CKey* key = m_vagArchive.OpenKey(name);

	if (!key)
	{
		return;
	}

	size_t size = key->GetSize();
	u8* buffer = (u8*)zmalloc(size);
	m_vagArchive.Fetch(key, buffer, size);

	tag_VAGHeader header;
	
	s16* data = vagDecode(buffer, header);
	
	m_snd_len = header.samples;
	SDL_AudioSpec audioSpec { SDL_AUDIO_S16BE, 1, (s32)header.rate };
	m_audiostream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec, NULL, NULL);

	SDL_ResumeAudioStreamDevice(m_audiostream);

	if (SDL_GetAudioStreamAvailable(m_audiostream) < (s32)m_snd_len)
	{
		SDL_PutAudioStreamData(m_audiostream, data, key->GetSize());
	}
	
	m_vagArchive.CloseKey(key);
}


void CSnd::AddNewCSnd(CSnd* sound)
{
	if (!m_isDisabled)
	{
		m_soundmap[sound->m_name] = sound;
		m_soundlist.insert(m_soundlist.begin(), sound);
	}
}

CSnd* CSnd::GetSoundByName(const char* name)
{
	if (m_isDisabled)
	{
		return NULL;
	}

	auto sound = m_soundmap.find(name);

	if (sound == m_soundmap.end())
	{
		return NULL;
	}
	else
	{
		return sound->second;
	}

	return NULL;
}

bool CSnd::GetSubtitles()
{
	return m_bShowSubtitles;
}

float CSnd::CalcVol(f32 volume, f32 masterVolume)
{
	return 0.0f;
}

void CSnd::LoadCSnd(_zrdr* reader)
{

}