#include "zgame.h"

#include "ai/ai_main.h"
#include "anim/anim_main.h"
#include "entity/ent_main.h"
#include "node/node_main.h"
#include "valve/valve_main.h"
#include "util/util_main.h"
#include "world/zworld.h"

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