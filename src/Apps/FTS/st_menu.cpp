#include "gamez/zGame/zgame.h"
#include "gamez/zInput/zinput.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zVideo/zvid.h"

CMenuState::CMenuState()
{
	m_name = zstrdup("MenuState");
	m_skip = 0;
	m_skip_swap = 0;

	TtySoundString = CSaferStr();
	BackSoundString = CSaferStr();

	SelectionSound = NULL;

	strncpy(m_DefaultMenu, "dlgIntroScreen.rdr", 64);

	TtySoundString.reserve(64);
	BackSoundString.reserve(64);
}

bool CMenuState::Init()
{
	CInput::Flush();

	if (m_skip == 0)
	{
		if (auto archive = CRdrArchive::AddArchive("readerc.zar", "run/ui"))
		{

		}
	}

	return true;
}

void CMenuState::Tick(f32 dT)
{
	zVid_Swap(false);
}