#include "zsnd_csnd.h"

CSnd::CSnd()
{
	if (!m_isDisabled)
	{
		volume = 1.0f;
		field5_0x8 = 0;
		range = 160.0f;
		field7_0x10 = 430.0f;
		bank = NULL;
		curSndID = -1;
		field_0x1c = 0;
		field14_0x20 = NULL;
		field15_0x24 = NULL;
		field16_0x28 = NULL;
		field_0x1e = 0;
		subtitle = 0;
		subtitleTime = 0.0f;
		subtitleValve = NULL;
		offset1 = 0;
		offset2 = 0;
		oneshot = false;
		field_0x40 = 0;
		type = 1;
		CSndInstance::m_sound_instance_pool.reserve(48);
	}
}

void CSndJukebox::Play(MUSIC_MODE mode, undefined8 param_2)
{

}