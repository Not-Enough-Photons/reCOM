#include "gamez/zCamera/zcam.h"
#include "gamez/zGame/zgame.h"
#include "gamez/zInput/zinput.h"
#include "gamez/zRender/zrender.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zVideo/zvid.h"

bool LoadWorld(const char* name);

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
		zar::CZAR* archive = CRdrArchive::AddArchive("readerc.zar", "run/ui");

		if (archive)
		{
			archive->ReOpen(CRdrArchive::version, 1);
		}

		// zdb::CTexManager::m_texmanager->doSetupBuffers();
		
		LoadWorld("ui");

		if (zdb::CWorld::m_world)
		{
			zdb::CCamera* camera = zdb::CWorld::m_world->m_camera;
			
			camera->SetPosition(320.0f, 0.0f, 320.0f);
			camera->Update(zdb::tag_ZCAM_TYPE::ZCAM_NORMAL);
			zdb::CVisual::m_camera = camera;
			thePipe.m_camera = camera;
		}
	}

	return true;
}

void CMenuState::Tick(f32 dT)
{
	// The world has to exist in order for nodes to be rendered
	if (zdb::CWorld::m_world != NULL)
	{
		if (zdb::CWorld::m_world->m_camera != NULL)
		{
			zdb::CWorld::m_world->m_camera->Update(zdb::tag_ZCAM_TYPE::ZCAM_NORMAL);
		}
	}

	glfwPollEvents();
	zVid_ClearColor(0.0f, 0.0f, 0.0f);
	zVid_Swap(false);
}