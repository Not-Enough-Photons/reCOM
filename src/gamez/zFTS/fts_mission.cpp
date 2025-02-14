#include "gamez/zAnim/zanim.h"
#include "gamez/zBone/zbone.h"
#include "gamez/zCharacter/zchar.h"
#include "gamez/zFTS/zfts.h"
#include "gamez/zNetwork/znet.h"
#include "gamez/zSeal/zseal.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zVehicle/zvehicle.h"

CMission theMission;

void UpdateMissionArchive(const char* type, const char* path)
{
	std::string pathstr;
	pathstr.append(gamez_GamePath);

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
			pathstr.assign(gamez_GamePath, pathstr.length());
			pathstr.assign("D:/run/", pathstr.length());

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

bool CMission::Init()
{
	char path_buf[256];
	
	// TODO:
	// Implement all these
	ZAnim.Open();
	CSealCtrlAi::RegisterCommands();
	// CValve::RegisterCommands();
	// zdb::CCamera::RegisterAnimCommands();
	// CAppCamera::RegisterAnimCommands();
	// CftsPlayer::RegisterAnimCommands();
	// zdb::CWind::RegisterAnimCommands();

	ZAnim.AddCmd("HUD_ON", HUDCmdParseOn, NULL, HUDCmdTickControlSwitch, NULL);
	ZAnim.AddCmd("HUD_OFF", HUDCmdParseOff, NULL, HUDCmdTickControlSwitch, NULL);
	ZAnim.AddCmd("HUD_LETTERBOX_ON", HUDLetterBoxCmdParseOn, NULL, HUDLetterBoxCmdTick, NULL);
	ZAnim.AddCmd("HUD_LETTERBOX_OFF", HUDLetterBoxCmdParseOff, NULL, HUDLetterBoxCmdTick, NULL);

	m_chars_loaded = false;

	sprintf_s(path_buf, 256, "%s/ui", gamez_GamePath);
	
	CRdrArchive::AddArchive("readerc.zar", gamez_GamePath);
	CRdrArchive::AddArchive("readerc.zar", path_buf);
	CRdrArchive::OpenAll();

	zBoneInit();
	zBoneOpen();
	zBoneLoadAll();
	zBoneClose();

	CZNetGame* netgame = new CZNetGame();

	netgame->m_clock.m_max_game_time = 0;
	netgame->m_clock.m_game_time = 0;
	netgame->m_clock.m_time_in_round = 0;
	netgame->m_clock.m_initial_read = 0;
	netgame->m_clock.m_total_time = 0;
	netgame->m_clock.m_initial_read_set = false;
	netgame->m_clock.m_clock_running = false;
	netgame->Initialize();

	m_pNetGame = netgame;

	CRdrFile* hud_rdr = zrdr_read("hud.rdr", NULL, 0);

	if (hud_rdr)
	{
		zrdr_findPNT2D(hud_rdr, "static_radio", &m_pNetGame->m_static_radio_loc);
		zrdr_findPNT2D(hud_rdr, "dynamic_radio", &m_pNetGame->m_dynamic_radio_loc);
	}

	zrdr_free(hud_rdr);

	CValve::Open("global_valves.rdr", VALVE_TYPE::VTYPE_PERM);
	m_valve_complete = CValve::Create("mission_complete", VALVE_TYPE::VTYPE_PERM);
	m_valve_failure = CValve::Create("mission_failure", VALVE_TYPE::VTYPE_PERM);
	m_valve_abort = CValve::Create("mission_abort", VALVE_TYPE::VTYPE_PERM);
	m_valve_timeout = CValve::Create("mission_timeout", VALVE_TYPE::VTYPE_PERM);
	m_valve_nofade = CValve::Create("mission_nofade", VALVE_TYPE::VTYPE_PERM);

	m_ordersRdr = zrdr_read("orders.rdr", NULL, 0);
	m_materialsRdr = zrdr_read("materials.rdr", NULL, 0);
	m_decalsRdr = zrdr_read("decals.rdr", NULL, 0);
	m_fontsRdr = zrdr_read("fonts.rdr", NULL, 0);
	m_messagesRdr = zrdr_read("messages.rdr", NULL, 0);
	m_subtitlesRdr = zrdr_read("subtitles.rdr", NULL, 0);
	m_smallmessagesRdr = zrdr_read("small_messages.rdr", NULL, 0);

	// Particle::Init();
	SealInitCharacterDynamics();

	m_vehicleRdr = new CVehicleRdr();

	// AnimSet::Load();
	CCharacterType::Open("character.rdr");
	// CCtrlrConfigs::Init()
	
	// ZuiInit();
	// hudInit();

	// CTurret::Init("ai_turrets.rdr", "data/common");
	CRdrArchive::RemoveArchive("readerc.zar", gamez_GamePath);

	return true;
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