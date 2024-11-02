#include "znet_main.h"

#include "valve/valve_main.h"
#include "ui/zui_main.h"

bool g_bJoiningRandomGame;
int myConnectionIndex;

CUIVariable* uiv_LobbyWorldNameVar;
CUIVariable* uiv_GameNameVar;
CUIVariable* uiv_ClanNameVar;
CUIVariable* uiv_ClanDescription;

int dme_joined_count;
int accum_dme_joined_count;

bool ForceReport;

void CZOnlineLobby::Init()
{
	if (!started)
	{
		started = true;
		myConnectionIndex = 0xffffffff;
		g_bJoiningRandomGame = false;

		uiv_LobbyWorldNameVar = theUIVarManager.Add("MEDIUS_LOBBY_NAME", NULL, UIVAR_LONGEVITY::value_02);
		uiv_GameNameVar = theUIVarManager.Add("GAMENAMEVAR", NULL, UIVAR_LONGEVITY::value_02);
		uiv_ClanNameVar = theUIVarManager.Add("CLANNAMEVAR", NULL, UIVAR_LONGEVITY::value_02);
		uiv_ClanDescription = theUIVarManager.Add("Clan_Description", NULL, UIVAR_LONGEVITY::value_02);

		dme_joined_count = 0;
		accum_dme_joined_count = 0;

		onlineStatusValve = CValve::Create("socom_online_state", VALVE_TYPE::PERM);
		ForceReport = false;

		// TODO:
		// Implement std::deque as per the decomp
	}
}