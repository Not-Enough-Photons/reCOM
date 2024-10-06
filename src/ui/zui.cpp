#include "zui_main.h"

namespace zdb
{
	const char* CZUI::GetTeamName(zdb::FireTeam team)
	{
		switch (team)
		{
		case zdb::FireTeam::FIRETEAM:
			return "FIRETEAM";
		case zdb::FireTeam::ABLE:
			return "ABLE";
		case zdb::FireTeam::BRAVO:
			return "BRAVO";
		case zdb::FireTeam::ESCORTEE:
			return "ESCORTEE";
		case zdb::FireTeam::FRIENDLY:
			return "FRIENDLY";
		case zdb::FireTeam::NEUTRAL:
			return "NEUTRAL";
		case zdb::FireTeam::TURRETS:
			return "TURRETS";
		case zdb::FireTeam::SUPPORT:
			return "SUPPORT";
		case zdb::FireTeam::HOSTAGE:
			return "HOSTAGE";
		case zdb::FireTeam::ENEMIES:
			return "ENEMIES";
		case zdb::FireTeam::ALLIES:
			return "ALLIES";
		}

		return "FT_UNKNOWN";
	}

	const char* CZUI::GetRawCommandType(zdb::SealCommand command)
	{
		switch (command)
		{
		case zdb::SealCommand::CMD_UNKNOWN:
			return "CMD_UNKNOWN";
		case zdb::SealCommand::CMD_ACTION:
			return "CMD_ACTION";
		case zdb::SealCommand::CMD_DEPLOY:
			return "CMD_DEPLOY";
		case zdb::SealCommand::CMD_FIREATWILL:
			return "CMD_FIREATWILL";
		case zdb::SealCommand::CMD_FOLLOW:
			return "CMD_FOLLOW";
		case zdb::SealCommand::CMD_HOLDPOS:
			return "CMD_HOLDPOS";
		case zdb::SealCommand::CMD_HOLDFIRE:
			return "CMD_HOLDFIRE";
		case zdb::SealCommand::CMD_REGROUP:
			return "CMD_REGROUP";
		case zdb::SealCommand::CMD_ESCORT:
			return "CMD_ESCORT";
		case zdb::SealCommand::CMD_RUNTO:
			return "CMD_RUNTO";
		case zdb::SealCommand::CMD_MOVETO:
			return "CMD_MOVETO";
		case zdb::SealCommand::CMD_STEALTHTO:
			return "CMD_STEALTHTO";
		case zdb::SealCommand::CMD_ATTACKTO:
			return "CMD_ATTACKTO";
		case zdb::SealCommand::CMD_LEADTO:
			return "CMD_LEADTO";
		case zdb::SealCommand::CMD_COVERTARGET:
			return "CMD_COVERTARGET";
		case zdb::SealCommand::CMD_LASETARGET:
			return "CMD_LASETARGET";
		case zdb::SealCommand::CMD_BREACH:
			return "CMD_BREACH";
		case zdb::SealCommand::CMD_GETDOWN:
			return "CMD_GETDOWN";
		case zdb::SealCommand::CMD_PULLOUT:
			return "CMD_PULLOUT";
		case zdb::SealCommand::CMD_OVERWATCH:
			return "CMD_OVERWATCH";
		case zdb::SealCommand::CMD_SUPPORT:
			return "CMD_SUPPORT";
		case zdb::SealCommand::CMD_EXTRACT:
			return "CMD_EXTRACT";
		case zdb::SealCommand::CMD_CLEARAREA:
			return "CMD_CLEARAREA";
		case zdb::SealCommand::CMD_RESTRAIN:
			return "CMD_RESTRAIN";
		case zdb::SealCommand::CMD_REMOVEKILLS:
			return "CMD_REMOVEKILLS";
		case zdb::SealCommand::CMD_AWAKE:
			return "CMD_AWAKE";
		case zdb::SealCommand::CMD_SLEEP:
			return "CMD_SLEEP";
		case zdb::SealCommand::CMD_AMBUSH:
			return "CMD_AMBUSH";
		}

		return "CMD_UNKNOWN";
	}

	const char* CZUI::GetCommandDisplayName(zdb::SealCommand command)
	{
		switch (command)
		{
		case zdb::SealCommand::CMD_ACTION:
			return "CMD_ACTION";
		case zdb::SealCommand::CMD_DEPLOY:
			return "DEPLOY";
		case zdb::SealCommand::CMD_FIREATWILL:
			return "FIRE AT WILL";
		case zdb::SealCommand::CMD_FOLLOW:
			return "FOLLOW";
		case zdb::SealCommand::CMD_HOLDPOS:
			return "HOLD POSITION";
		case zdb::SealCommand::CMD_HOLDFIRE:
			return "HOLD FIRE";
		case zdb::SealCommand::CMD_REGROUP:
			return "REGROUP";
		case zdb::SealCommand::CMD_ESCORT:
			return "ESCORT";
		case zdb::SealCommand::CMD_RUNTO:
			return "RUN TO";
		case zdb::SealCommand::CMD_MOVETO:
			return "MOVE TO";
		case zdb::SealCommand::CMD_STEALTHTO:
			return "STEALTH TO";
		case zdb::SealCommand::CMD_ATTACKTO:
			return "ATTACK TO";
		case zdb::SealCommand::CMD_LEADTO:
			return "LEAD TO";
		case zdb::SealCommand::CMD_COVERTARGET:
			return "COVER TARGET";
		case zdb::SealCommand::CMD_LASETARGET:
			return "LASE TARGET";
		case zdb::SealCommand::CMD_BREACH:
			return "BREACH";
		case zdb::SealCommand::CMD_GETDOWN:
			return "GET DOWN";
		case zdb::SealCommand::CMD_PULLOUT:
			return "PULL OUT";
		case zdb::SealCommand::CMD_OVERWATCH:
			return "OVERWATCH";
		case zdb::SealCommand::CMD_EXTRACT:
			return "CMD_EXTRACT";
		}

		return GetRawCommandType(command);
	}

	const char* CZUI::GetProperRegroupDisplay(zdb::SealCommand command)
	{
		if (command == zdb::SealCommand::CMD_REGROUP)
		{
			return "RE GROUP";
		}

		return GetCommandDisplayName(command);
	}

	const char* CZUI::GetCommandDescription(zdb::SealCommand command)
	{
		switch (command)
		{
		case zdb::SealCommand::CMD_ACTION:
			return "CMD_ACTION";
		case zdb::SealCommand::CMD_DEPLOY:
			return "Throw or place any item at crosshairs . . .";
		case zdb::SealCommand::CMD_FIREATWILL:
			return "Take any and every open shot";
		case zdb::SealCommand::CMD_FOLLOW:
			return "Follow me";
		case zdb::SealCommand::CMD_HOLDPOS:
			return "Stay where you are";
		case zdb::SealCommand::CMD_HOLDFIRE:
			return "Shoot only when shot at";
		case zdb::SealCommand::CMD_REGROUP:
			return "Regroup at team leader's position";
		case zdb::SealCommand::CMD_ESCORT:
			return "Person under reticule will follow";
		case zdb::SealCommand::CMD_RUNTO:
			return "Run to . . .";
		case zdb::SealCommand::CMD_MOVETO:
			return "Move out to . . .";
		case zdb::SealCommand::CMD_STEALTHTO:
			return "Using shadows and coverage, move to . . .";
		case zdb::SealCommand::CMD_ATTACKTO:
			return "Take all available shots and move to . . .";
		case zdb::SealCommand::CMD_LEADTO:
			return "Escort me to . . .";
		case zdb::SealCommand::CMD_COVERTARGET:
			return "Covering fire at my crosshairs";
		case zdb::SealCommand::CMD_LASETARGET:
			return "Laser designate guided weapon target . . .";
		case zdb::SealCommand::CMD_BREACH:
			return "BREACH";
		case zdb::SealCommand::CMD_GETDOWN:
			return "Get down on the ground";
		case zdb::SealCommand::CMD_PULLOUT:
			return "PULLOUT";
		case zdb::SealCommand::CMD_OVERWATCH:
			return "Assume overwatch position";
		case zdb::SealCommand::CMD_EXTRACT:
			return "Extract escort or hostage";
		case zdb::SealCommand::CMD_REMOVEKILLS:
			return "Remove any hostiles";
		}

		return GetRawCommandType(command);
	}

	void CZUI::InitializeCommandEntry(zdb::SealCommand command)
	{
		const char* fireTeam;
		const char* commandType;
		const char* commandDisplayName;
		const char* regroup;
		const char* commandDescription;

		// Fireteam (including Able and Bravo)
		fireTeam = GetTeamName(zdb::FireTeam::FIRETEAM);
		commandType = GetRawCommandType(command);
		commandDisplayName = GetCommandDisplayName(command);
		regroup = GetProperRegroupDisplay(command);
		commandDescription = GetCommandDescription(command);
		// FUN_004f4ff0(commandType, fireTeam, commandDisplayName, regroup, commandDescription, 0);

		// Able element (Specter and Jester)
		fireTeam = GetTeamName(zdb::FireTeam::ABLE);
		commandType = GetRawCommandType(command);
		commandDisplayName = GetCommandDisplayName(command);
		regroup = GetProperRegroupDisplay(command);
		commandDescription = GetCommandDescription(command);
		// FUN_004f4ff0(commandType, fireTeam, commandDisplayName, regroup, commandDescription, 0);

		// Bravo element (Wardog, Vandal, and those other two blokes)
		fireTeam = GetTeamName(zdb::FireTeam::BRAVO);
		commandType = GetRawCommandType(command);
		commandDisplayName = GetCommandDisplayName(command);
		regroup = GetProperRegroupDisplay(command);
		commandDescription = GetCommandDescription(command);
		// FUN_004f4ff0(commandType, fireTeam, commandDisplayName, regroup, commandDescription, 0);
	}

	void CZUI::SendUIMessage(float time, const char* message, char* messagePtr, void* param_4, void* param_5, int param_6)
	{
		C2DMessageString str;
	}
}