#include "zui_main.h"

namespace zdb
{
	const char* CZUI::GetCommandDescription(CommandDescType desc)
	{
		const char* description;

		switch (desc)
		{
		case DESC_BASE:
			description = "CMD_ACTION";
			break;
		case DESC_THROW_ITEM:
			description = "Throw or place item at crosshairs . . .";
			break;
		case DESC_FIRE_AT_WILL:
			description = "Take any and every open shot";
			break;
		case DESC_FOLLOW:
			description = "Follow me";
			break;
		case DESC_HOLD_POSITION:
			description = "Stay where you are";
			break;
		case DESC_HOLD_FIRE:
			description = "Shoot only when shot at";
			break;
		case DESC_REGROUP:
			description = "Regroup at team leader's position";
			break;
		case DESC_HOSTAGE_FOLLOW:
			description = "Person under reticule will follow";
			break;
		case DESC_RUN_TO:
			description = "Run to . . .";
			break;
		case DESC_MOVE_TO:
			description = "Move out to . . .";
			break;
		case DESC_STEALTH_TO:
			description = "Using shadows and coverage, move to . . .";
			break;
		case DESC_ATTACK_TO:
			description = "Take all available shots and move to . . .";
			break;
		case DESC_ESCORT_TO:
			description = "Escort me to . . .";
			break;
		case DESC_COVER_TARGET:
			description = "Covering fire at my crosshairs";
			break;
		case DESC_LASER:
			description = "Laser designate guided weapon target . . .";
			break;
		case DESC_BREACH:
			description = "BREACH";
			break;
		case DESC_GET_DOWN:
			description = "Get down on the ground";
			break;
		case DESC_PULL_OUT:
			description = "PULLOUT";
			break;
		case DESC_OVERWATCH:
			description = "Assume overwatch position";
			break;
		case DESC_EXTRACT_HOSTAGE:
			description = "Extract escort or hostage";
			break;
		case DESC_REMOVE_KILLS:
			description = "Remove any hostiles";
			break;
		default:
			// description = FUN_002ca4a0();
			break;
		}

		return description;
	}

	void CZUI::SendUIMessage(float time, const char* message, char* messagePtr, void* param_4, void* param_5, int param_6)
	{
		C2DMessageString str;
	}
}