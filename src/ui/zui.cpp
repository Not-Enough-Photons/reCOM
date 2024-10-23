#include "zui_main.h"

const char* CZUI::GetTeamName(FIRE_TEAM team)
{
	switch (team)
	{
	case FIRE_TEAM::FIRETEAM:
		return "FIRETEAM";
	case FIRE_TEAM::ABLE:
		return "ABLE";
	case FIRE_TEAM::BRAVO:
		return "BRAVO";
	case FIRE_TEAM::ESCORTEE:
		return "ESCORTEE";
	case FIRE_TEAM::FRIENDLY:
		return "FRIENDLY";
	case FIRE_TEAM::NEUTRAL:
		return "NEUTRAL";
	case FIRE_TEAM::TURRETS:
		return "TURRETS";
	case FIRE_TEAM::SUPPORT:
		return "SUPPORT";
	case FIRE_TEAM::HOSTAGE:
		return "HOSTAGE";
	case FIRE_TEAM::ENEMIES:
		return "ENEMIES";
	case FIRE_TEAM::ALLIES:
		return "ALLIES";
	}

	return "FT_UNKNOWN";
}

const char* CZUI::GetRawCommandType(FT_COMMAND command)
{
	switch (command)
	{
	case FT_COMMAND::CMD_UNKNOWN:
		return "CMD_UNKNOWN";
	case FT_COMMAND::CMD_ACTION:
		return "CMD_ACTION";
	case FT_COMMAND::CMD_DEPLOY:
		return "CMD_DEPLOY";
	case FT_COMMAND::CMD_FIREATWILL:
		return "CMD_FIREATWILL";
	case FT_COMMAND::CMD_FOLLOW:
		return "CMD_FOLLOW";
	case FT_COMMAND::CMD_HOLDPOS:
		return "CMD_HOLDPOS";
	case FT_COMMAND::CMD_HOLDFIRE:
		return "CMD_HOLDFIRE";
	case FT_COMMAND::CMD_REGROUP:
		return "CMD_REGROUP";
	case FT_COMMAND::CMD_ESCORT:
		return "CMD_ESCORT";
	case FT_COMMAND::CMD_RUNTO:
		return "CMD_RUNTO";
	case FT_COMMAND::CMD_MOVETO:
		return "CMD_MOVETO";
	case FT_COMMAND::CMD_STEALTHTO:
		return "CMD_STEALTHTO";
	case FT_COMMAND::CMD_ATTACKTO:
		return "CMD_ATTACKTO";
	case FT_COMMAND::CMD_LEADTO:
		return "CMD_LEADTO";
	case FT_COMMAND::CMD_COVERTARGET:
		return "CMD_COVERTARGET";
	case FT_COMMAND::CMD_LASETARGET:
		return "CMD_LASETARGET";
	case FT_COMMAND::CMD_BREACH:
		return "CMD_BREACH";
	case FT_COMMAND::CMD_GETDOWN:
		return "CMD_GETDOWN";
	case FT_COMMAND::CMD_PULLOUT:
		return "CMD_PULLOUT";
	case FT_COMMAND::CMD_OVERWATCH:
		return "CMD_OVERWATCH";
	case FT_COMMAND::CMD_SUPPORT:
		return "CMD_SUPPORT";
	case FT_COMMAND::CMD_EXTRACT:
		return "CMD_EXTRACT";
	case FT_COMMAND::CMD_CLEARAREA:
		return "CMD_CLEARAREA";
	case FT_COMMAND::CMD_RESTRAIN:
		return "CMD_RESTRAIN";
	case FT_COMMAND::CMD_REMOVEKILLS:
		return "CMD_REMOVEKILLS";
	case FT_COMMAND::CMD_AWAKE:
		return "CMD_AWAKE";
	case FT_COMMAND::CMD_SLEEP:
		return "CMD_SLEEP";
	case FT_COMMAND::CMD_AMBUSH:
		return "CMD_AMBUSH";
	}

	return "CMD_UNKNOWN";
}

const char* CZUI::GetCommandDisplayName(FT_COMMAND command)
{
	switch (command)
	{
	case FT_COMMAND::CMD_ACTION:
		return "CMD_ACTION";
	case FT_COMMAND::CMD_DEPLOY:
		return "DEPLOY";
	case FT_COMMAND::CMD_FIREATWILL:
		return "FIRE AT WILL";
	case FT_COMMAND::CMD_FOLLOW:
		return "FOLLOW";
	case FT_COMMAND::CMD_HOLDPOS:
		return "HOLD POSITION";
	case FT_COMMAND::CMD_HOLDFIRE:
		return "HOLD FIRE";
	case FT_COMMAND::CMD_REGROUP:
		return "REGROUP";
	case FT_COMMAND::CMD_ESCORT:
		return "ESCORT";
	case FT_COMMAND::CMD_RUNTO:
		return "RUN TO";
	case FT_COMMAND::CMD_MOVETO:
		return "MOVE TO";
	case FT_COMMAND::CMD_STEALTHTO:
		return "STEALTH TO";
	case FT_COMMAND::CMD_ATTACKTO:
		return "ATTACK TO";
	case FT_COMMAND::CMD_LEADTO:
		return "LEAD TO";
	case FT_COMMAND::CMD_COVERTARGET:
		return "COVER TARGET";
	case FT_COMMAND::CMD_LASETARGET:
		return "LASE TARGET";
	case FT_COMMAND::CMD_BREACH:
		return "BREACH";
	case FT_COMMAND::CMD_GETDOWN:
		return "GET DOWN";
	case FT_COMMAND::CMD_PULLOUT:
		return "PULL OUT";
	case FT_COMMAND::CMD_OVERWATCH:
		return "OVERWATCH";
	case FT_COMMAND::CMD_EXTRACT:
		return "CMD_EXTRACT";
	}

	return GetRawCommandType(command);
}

const char* CZUI::GetProperRegroupDisplay(FT_COMMAND command)
{
	if (command == FT_COMMAND::CMD_REGROUP)
	{
		return "RE GROUP";
	}

	return GetCommandDisplayName(command);
}

const char* CZUI::GetCommandDescription(FT_COMMAND command)
{
	switch (command)
	{
	case FT_COMMAND::CMD_ACTION:
		return "CMD_ACTION";
	case FT_COMMAND::CMD_DEPLOY:
		return "Throw or place any item at crosshairs . . .";
	case FT_COMMAND::CMD_FIREATWILL:
		return "Take any and every open shot";
	case FT_COMMAND::CMD_FOLLOW:
		return "Follow me";
	case FT_COMMAND::CMD_HOLDPOS:
		return "Stay where you are";
	case FT_COMMAND::CMD_HOLDFIRE:
		return "Shoot only when shot at";
	case FT_COMMAND::CMD_REGROUP:
		return "Regroup at team leader's position";
	case FT_COMMAND::CMD_ESCORT:
		return "Person under reticule will follow";
	case FT_COMMAND::CMD_RUNTO:
		return "Run to . . .";
	case FT_COMMAND::CMD_MOVETO:
		return "Move out to . . .";
	case FT_COMMAND::CMD_STEALTHTO:
		return "Using shadows and coverage, move to . . .";
	case FT_COMMAND::CMD_ATTACKTO:
		return "Take all available shots and move to . . .";
	case FT_COMMAND::CMD_LEADTO:
		return "Escort me to . . .";
	case FT_COMMAND::CMD_COVERTARGET:
		return "Covering fire at my crosshairs";
	case FT_COMMAND::CMD_LASETARGET:
		return "Laser designate guided weapon target . . .";
	case FT_COMMAND::CMD_BREACH:
		return "BREACH";
	case FT_COMMAND::CMD_GETDOWN:
		return "Get down on the ground";
	case FT_COMMAND::CMD_PULLOUT:
		return "PULLOUT";
	case FT_COMMAND::CMD_OVERWATCH:
		return "Assume overwatch position";
	case FT_COMMAND::CMD_EXTRACT:
		return "Extract escort or hostage";
	case FT_COMMAND::CMD_REMOVEKILLS:
		return "Remove any hostiles";
	}

	return GetRawCommandType(command);
}

void CZUI::InitializeCommandEntry(FT_COMMAND command)
{
	const char* fireTeam;
	const char* commandType;
	const char* commandDisplayName;
	const char* regroup;
	const char* commandDescription;

	// Fireteam (including Able and Bravo)
	fireTeam = GetTeamName(FIRE_TEAM::FIRETEAM);
	commandType = GetRawCommandType(command);
	commandDisplayName = GetCommandDisplayName(command);
	regroup = GetProperRegroupDisplay(command);
	commandDescription = GetCommandDescription(command);
	// FUN_004f4ff0(commandType, fireTeam, commandDisplayName, regroup, commandDescription, 0);

	// Able element (Specter and Jester)
	fireTeam = GetTeamName(FIRE_TEAM::ABLE);
	commandType = GetRawCommandType(command);
	commandDisplayName = GetCommandDisplayName(command);
	regroup = GetProperRegroupDisplay(command);
	commandDescription = GetCommandDescription(command);
	// FUN_004f4ff0(commandType, fireTeam, commandDisplayName, regroup, commandDescription, 0);

	// Bravo element (Wardog, Vandal, and those other two blokes)
	fireTeam = GetTeamName(FIRE_TEAM::BRAVO);
	commandType = GetRawCommandType(command);
	commandDisplayName = GetCommandDisplayName(command);
	regroup = GetProperRegroupDisplay(command);
	commandDescription = GetCommandDescription(command);
	// FUN_004f4ff0(commandType, fireTeam, commandDisplayName, regroup, commandDescription, 0);
}