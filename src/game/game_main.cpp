#include "zgame.h"

#include "ai/ai_main.h"
#include "anim/anim_main.h"
#include "audio/zsnd_csnd.h"
#include "entity/ent_main.h"
#include "input/input_main.h"
#include "node/node_main.h"
#include "node/node_world.h"
#include "render/zrnd_main.h"
#include "reader/zrdr_main.h"
#include "system/zsys_main.h"
#include "texture/ztex_main.h"
#include "ui/zui_main.h"
#include "util/util_main.h"
#include "valve/valve_main.h"
#include "video/zvid_main.h"

void game_main()
{
	zUtilInit("ftslog.txt");
	COurGame::StartEngine();
	CGame::StartPlay();

	while (true)
	{
		CGame::Tick();
	}
}

bool CGame::StartEngine()
{
	InitSystemTuners();
	CSched_Manager::Clear("zTaskScheduler");
	zdb::CRipple::Init();
	zdb::CTextureFX::Init();
	CValve::Init();
	zVid_Init();
	zdb::CTexture::Init();
	C2D::Init();
	zdb::CWorld::Init();
	zSysReset();
	zVid_Open();
	C2D::Open();
	CInput::Init();
	zRndrInit();
	CSndInstance::InitInstancePool(48);
	CInput::CreatePad(0);
	CInput::CreatePad(1);
	zMath_Init();
	CPipe::Init();
	CGameStateChangeCmd::CreatePool(16);
	CSealAnim* sealAnim = new CSealAnim();
    zdb::CZSealBody::m_sealanim = sealAnim;
	return true;
}

bool COurGame::StartEngine()
{
	bool success = CGame::StartEngine();
	if (success)
	{
		CVideo::RestoreImage("RUN\\LOADING.RAW");
		zVid_Swap(1);
		zdb::CTexManager::doAddBuffer(0.0f, 1.0f, 0x4b9590, "default");
		CMission::Init();
		// int clock = sceCdReadClock(...)
		// TODO:
		// add more past CMission::Init();
	}

	return true;
}

void CMission::Init()
{
	CZAnimMain::Open("ZAnim");
	zdb::CSealCtrlAi::RegisterCommands();
	CValve::RegisterCommands();
	zdb::CCamera::RegisterAnimCommands();
	zdb::CAppCamera::RegisterAnimCommands();
	zdb::CftsPlayer::RegisterAnimCommands();
	zdb::CWind::RegisterAnimCommands();
}

void CMission::Read(zrdr* reader)
{
	weather_factor = 0.0f;
	seal_command = 4;
	recycle_time = 60.0f;
	recycle_range = 10000.0f;
	respawn_time = 5.0f;
	respawn_fade = 0.75f;

	auto aiParams = zrdr_findtag(reader, "ai_params");
	if (aiParams != NULL)
	{
		zrdr_findreal(aiParams, "weather_factor", &weather_factor, 1);
		zrdr_findreal(aiParams, "respawn_time", &respawn_time, 1);
		zrdr_findreal(aiParams, "respawn_fade", &respawn_fade, 1);
		zrdr_findreal(aiParams, "recycle_time", &recycle_time, 1);
		bool success = zrdr_findreal(aiParams, "recycle_range", &recycle_range, 1);

		if (success)
		{
			recycle_range *= recycle_range;
		}

		FireTeam command
	}
}