#include "Apps/FTS/fts.h"

#include "gamez/zAnim/anim_main.h"
#include "gamez/zGame/zgame.h"
#include "gamez/zSystem/zsys_main.h"
#include "gamez/zVideo/zvid_main.h"
#include "gamez/zUI/zui.h"
#include "gamez/zRender/zrndr_main.h"

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
	CZSealBody::m_sealanim = sealAnim;
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
		theMission.Init();
		// int clock = sceCdReadClock(...)
		// TODO:
		// add more past CMission::Init();
	}

	return true;
}