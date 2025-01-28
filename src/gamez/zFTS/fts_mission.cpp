#include "gamez/zAnim/zanim.h"
#include "gamez/zFTS/zfts.h"
#include "gamez/zSystem/zsys.h"

CMission theMission;

void UpdateMissionArchive(const char* type, const char* path)
{
	std::string pathstr = "run/";

	if (type)
	{
		pathstr.assign("run/", pathstr.length());

		if (strncmp(type, "mp", 2) == 0)
		{
			pathstr.append("mp");
		}
		else
		{
			if (strncmp(type, "m", 1) == 0)
			{
				pathstr.append("sp/");
			}
		}
	}

	if (path)
	{
		if (strlen(path) != 0)
		{
			pathstr.assign("run/", pathstr.length());

			if (strncmp(path, "mp", 2) == 0)
			{
				pathstr.append("mp/", strlen("mp/"));
			}
			else
			{
				if (strncmp(path, "m", 1) == 0)
				{
					pathstr.append("sp/", strlen("sp/"));
				}
			}

			pathstr.append(path, strlen(path));
			CRdrArchive::AddArchive("readerm.zar", pathstr.c_str());
			CRdrArchive::OpenAll();
		}
	}
}

s32 FilterMissionFolder(const char* prefix, const char* infix, const char* postfix, char* output)
{
	s32 result = 0;

	if (!infix)
	{
		infix = "/";
	}

	// Multiplayer map?
	if (strncmp(prefix, "mp", 2) == 0)
	{
		result = sprintf_s(output, 128, "%s/mp/%s", infix, postfix);
	}
	else
	{
		// Singleplayer map?
		if (strncmp(prefix, "m", 1) == 0)
		{
			result = sprintf_s(output, 128, "%s/sp/%s", infix, postfix);
		}
		else
		{
			result = sprintf_s(output, 128, "%s/%s", infix, postfix);
		}
	}

	return result;
}

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

void CMission::PreOpen(const char* db)
{
	if (db && *db != '\0')
	{
		UpdateMissionArchive(m_database, db);
		m_database = m_db_string;
		strcpy_s(m_db_string, db);
	}
	else
	{
		m_database = NULL;
		return;
	}

	_zrdr* mission = zrdr_read("mission.rdr", NULL, 0);
	char* loadingscreenassets = zrdr_findstring(mission, "LoadingScreenAssets");

	if (!loadingscreenassets)
	{
		m_strLoadingScrLib.replace(0, 0, 0);
	}
	else
	{
		size_t len = strlen(loadingscreenassets);
		m_strLoadingScrLib.assign(&loadingscreenassets, len);
	}

	_zrdr* uivars = zrdr_findtag(mission, "UiVars");
	u32 idx = 0;
	
	while (true)
	{
		if (!uivars)
		{
			break;
		}
	}
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