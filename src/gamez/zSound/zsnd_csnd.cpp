#include "zsnd.h"

#include "gamez/zReader/zrdr.h"

int g_iReverbTime = 0;

CSnd::CSnd()
{
	if (!m_isDisabled)
	{

	}
}

void CSnd::Init()
{
	
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

float CSnd::CalcVol(float volume, float masterVolume)
{
	return 0.0f;
}

void CSnd::LoadCSnd(_zrdr* reader)
{

}