#include "zsnd.h"

#include "gamez/zReader/zrdr.h"

int g_iReverbTime = 0;

CSnd::CSnd()
{
	if (!m_isDisabled)
	{
		m_name = 0;
		m_volume = 1.0f;
		m_range = 160.0f;
		m_field7_0x10 = 430.0f;
		m_bank = NULL;
		m_curSndID = -1;
		m_field_0x1c = 0;
		m_field14_0x20 = NULL;
		m_field15_0x24 = NULL;
		m_field16_0x28 = NULL;
		m_field_0x1e = 0;
		m_subtitle = 0;
		m_subtitleTime = 0.0f;
		m_subtitleValve = NULL;
		m_offset1 = 0;
		m_offset2 = 0;
		m_oneshot = false;
		m_field_0x40 = 0;
		m_type = 1;
		CSndInstance::m_sound_instance_pool.reserve(48);
	}
}

void CSnd::Init()
{
	char* rootPath = "";

	if (!m_isDisabled)
	{
		if (!vagArchiveIsOpen)
		{
			vagArchiveIsOpen = true;
			int fd = CFileCD::Find("RUN\\SOUNDS\\VAGSTORE.ZAR;1");

			if (fd != 0)
			{
				m_vagoffset = fd + 4;
			}

			m_vagArchive->Open("RUN\\SOUNDS\\VAGSTORE.ZAR", 0, OpenFlags::READWRITE, 16);
			m_vagArchive->CloseKeepDir();
		}
	}

	if (!m_isDisabled && !bnkArchiveIsOpen)
	{
		bnkArchiveIsOpen = true;
		int fd = CFileCD::Find("RUN\\SOUNDS\\BNKSTORE.ZAR;1");

		if (fd != 0)
		{
			m_bnkoffset = fd + 4;
		}

		strcpy(rootPath, CFileIO::m_root_path);
		CFileIO::SetRootPath("cdrom0:\\");
		m_bnkArchive->Open("run/sounds/bnkstore.zar", 0, OpenFlags::READWRITE, 16);
		CFileIO::SetRootPath(rootPath);
		m_bnkArchive->CloseKeepDir();
	}

	// TODO:
	// write a replacement for the proprietary sound library 989snd.c
	// i may want to look into fmod...
	// snd_StartSoundSystem();
	CSndInstance::Init();

	if (sound_rdr == NULL)
	{
		sound_rdr = zrdr_read("sounds.rdr", NULL, 0);
	}

	// snd_SetReverbType(3, 3);
	if (m_hasreverb)
	{
		// snd_AutoReverb(3, 0, 0xf0, 3);
		m_hasreverb = false;
	}

	// theIOPManager->RegisterRebootCallback(IOPRebootHandler, 0);
	snd_system_initialized = true;
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
	float range = this->m_range;
	float output = 1.0f;

	if (range <= volume)
	{
		if (volume <= maxVol)
		{
			output = 1.0f - (volume - range) / (maxVol - range);
		}
		else
		{
			output = 0.0f;
		}
	}

	output = masterVolume * output * 1024.0f * CSndInstance::m_mastervol;
	return output;
}

void CSnd::LoadCSnd(_zrdr* reader)
{

}