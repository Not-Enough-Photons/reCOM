#include "fts.h"

void CMission::Init()
{
	CZAnimMain::Open("ZAnim");
	CSealCtrlAi::RegisterCommands();
	CValve::RegisterCommands();
	zdb::CCamera::RegisterAnimCommands();
	// CAppCamera::RegisterAnimCommands();
	CftsPlayer::RegisterAnimCommands();
	zdb::CWind::RegisterAnimCommands();
}

void CMission::Read(_zrdr* reader)
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
	}
}