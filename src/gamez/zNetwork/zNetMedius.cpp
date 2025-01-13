#include "znet.h"

#include "gamez/zValve/zvalve.h"
#include "gamez/zUI/zui.h"

bool g_bJoiningRandomGame;
s32 myConnectionIndex;

CUIVariable* uiv_LobbyWorldNameVar;
CUIVariable* uiv_GameNameVar;
CUIVariable* uiv_ClanNameVar;
CUIVariable* uiv_ClanDescription;

s32 dme_joined_count;
s32 accum_dme_joined_count;

bool ForceReport;

void CZOnlineLobby::Init()
{
	if (!started)
	{
		started = true;
		myConnectionIndex = 0xffffffff;
		g_bJoiningRandomGame = false;

		// uiv_LobbyWorldNameVar = theUIVarManager.Add("MEDIUS_LOBBY_NAME", NULL, UIVAR_LONGEVITY::UIVL_PERMANENT);
		// uiv_GameNameVar = theUIVarManager.Add("GAMENAMEVAR", NULL, UIVAR_LONGEVITY::UIVL_PERMANENT);
		// uiv_ClanNameVar = theUIVarManager.Add("CLANNAMEVAR", NULL, UIVAR_LONGEVITY::UIVL_PERMANENT);
		// uiv_ClanDescription = theUIVarManager.Add("Clan_Description", NULL, UIVAR_LONGEVITY::UIVL_PERMANENT);

		dme_joined_count = 0;
		accum_dme_joined_count = 0;

		onlineStatusValve = CValve::Create("socom_online_state", VALVE_TYPE::PERM);
		ForceReport = false;

		// TODO:
		// Implement std::deque as per the decomp
	}
}