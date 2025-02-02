#include "zgame.h"

#include "gamez/zFTS/zfts.h"
#include "gamez/zIMGUI/zimgui.h"
#include "gamez/zVideo/zvid.h"
#include "SDL3/SDL_time.h"
#include "SDL3/SDL_timer.h"

char* GetDatabase();

bool CGame::StartEngine()
{
	// zTaskScheduler.Clear();
	// zdb::CRipple::Init();
	// zdb::CTextureFX::Init();
	CValve::Init();
	zVid_Init(ZVID_MODE_NTSC);
	zdb::CTexture::Init();
	C2D::Init();
	// zdb::CWorld::Init();
	// zSysReset();
	zVid_Open();
	C2D::Open();
	CInput::Init();
	CZIMGUI::Init();
	// zRndrInit();
	// CSndInstance::InitInstancePool(48);
	CInput::CreatePad(0);
	CInput::CreatePad(1);
	// zMath_Init();
	// CPipe::Init();
	// CGameStateChangeCmd::CreatePool(16);
	// CSealAnim* sealAnim = new CSealAnim();
	// CZSealBody::m_sealanim = sealAnim;
	return true;
}

bool COurGame::StartEngine()
{
	bool success = CGame::StartEngine();
	if (success)
	{
		CVideo::RestoreImage("D:/RUN/LOADING.RAW", true);
		zVid_Swap(true);
		zdb::CTexManager::m_texmanager->doAddBuffer("default", 0.0f, 0.0f);
		
		theMission.Init();
		
		SDL_Time ticks;
		srand(SDL_GetCurrentTime(&ticks));

		char* db = GetDatabase();

		if (db)
		{
			size_t dblen = strlen(db);

			if (dblen != 0)
			{
				theMission.PreOpen(db);
			}
		}
	}

	return true;
}