#include "gamez/zAnim/zanim.h"
#include "gamez/zFTS/zfts.h"

CMission theMission;

void CMission::Init()
{
	// TODO:
	// Implement all these
	// CZAnimMain::Open("ZAnim");
	// CSealCtrlAi::RegisterCommands();
	// CValve::RegisterCommands();
	// zdb::CCamera::RegisterAnimCommands();
	// CAppCamera::RegisterAnimCommands();
	// CftsPlayer::RegisterAnimCommands();
	// zdb::CWind::RegisterAnimCommands();
}

void CMission::Read(_zrdr* reader)
{
	m_ai_params.weather_factor = 0.0f;
	m_ai_params.fireteam_command = FT_COMMAND::CMD_FOLLOW;
	m_ai_params.recycle_time = 60.0f;
	m_ai_params.recycle_range = 10000.0f;
	m_ai_params.respawn_time = 5.0f;
	m_ai_params.respawn_fade = 0.75f;

	auto aiParams = zrdr_findtag(reader, "ai_params");
	if (aiParams != NULL)
	{
		zrdr_findreal(aiParams, "weather_factor", &m_ai_params.weather_factor, 1);
		zrdr_findreal(aiParams, "respawn_time", &m_ai_params.respawn_time, 1);
		zrdr_findreal(aiParams, "respawn_fade", &m_ai_params.respawn_fade, 1);
		zrdr_findreal(aiParams, "recycle_time", &m_ai_params.recycle_time, 1);
		bool success = zrdr_findreal(aiParams, "recycle_range", &m_ai_params.recycle_range, 1);

		if (success)
		{
			m_ai_params.recycle_range *= m_ai_params.recycle_range;
		}
	}
}