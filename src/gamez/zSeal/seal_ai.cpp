#include "zseal.h"

namespace sealai
{
	const char* get_aiseq(AI_SEQUENCE sequence)
	{
		const char* str;

		switch (sequence)
		{
		case AIS_AWARE0:
			str = "on_aware0";
			break;
		case AIS_AWARE1:
			str = "on_aware0";
			break;
		case AIS_AWARE2:
			str = "on_aware0";
			break;
		case AIS_AWARE3:
			str = "on_aware0";
			break;
		default:
			str = "on_awarex";
		}

		return str;
	}

	AI_MODE get_mode(const char* name)
	{
		AI_MODE mode;
		return mode;
	}

	const char* get_stance(SEAL_STANCE stance)
	{
		return "";
	}

	SEAL_STANCE get_stance(const char* name)
	{
		SEAL_STANCE stance;
		return stance;
	}

	AI_STATE get_state(const char* name)
	{
		AI_STATE state;
		return state;
	}

	const char* get_state(AI_STATE state)
	{
		const char* str;

		switch (state)
		{
		case STATE_UNKNOWN:
			str = "unknown";
			break;
		case STATE_SCRIPT:
			str = "script";
			break;
		case STATE_HOLD:
			str = "hold";
			break;
		case STATE_AVOID:
			str = "avoid";
			break;
		case STATE_DEPLOY:
			str = "deploy";
			break;
		case STATE_LASING:
			str = "lasing";
			break;
		case STATE_SURRENDER:
			str = "surrender";
			break;
		case STATE_RESTRAINED:
			str = "restrained";
			break;
		case STATE_GOTO:
			str = "goto";
			break;
		case STATE_FOLLOW:
			str = "follow";
			break;
		case STATE_BREACH:
			str = "breach";
			break;
		case STATE_ACTION:
			str = "action";
			break;
		case STATE_PURSUE:
			str = "pursue";
			break;
		case STATE_ANIMATE:
			str = "animate";
			break;
		case STATE_CQB:
			str = "cqb";
			break;
		case STATE_FLEE:
			str = "flee";
			break;
		case STATE_PATHRECO:
			str = "pathreco";
			break;
		case STATE_RESCUED:
			str = "rescued";
			break;
		case STATE_SUSPENDED:
			str = "suspended";
			break;
		case STATE_SHOTAT:
			str = "shotat";
			break;
		case STATE_RELOAD:
			str = "reload";
			break;
		case STATE_NOAMMO:
			str = "noammo";
			break;
		case STATE_PICKUP:
			str = "pickup";
			break;
		case STATE_HOSTAGE:
			str = "hostage";
			break;
		case STATE_CORPSE:
			str = "corpse";
			break;
		case STATE_EVENT:
			str = "event";
			break;
		case STATE_TARGETING:
			str = "targeting";
			break;
		case STATE_GRENADE:
			str = "grenade";
			break;
		case STATE_STUNNED:
			str = "stunned";
			break;
		case STATE_RUSH:
			str = "rush";
			break;
		default:
			str = "undef";
		}

		return str;
	}
}

SEAL_VALVE CSealCtrlAi::get_valve(const char* valve)
{
	if (valve)
	{
		for (u32 i = 0; i < static_cast<u32>(SEAL_VALVE::VALVE_MAX); i++)
		{
			SEAL_VALVE seal_valve = static_cast<SEAL_VALVE>(i);
			const char* name = "";

			switch (seal_valve)
			{
			case SEAL_VALVE::VALVE_HOLDFIRE:
				name = "valve_holdfire";
			case SEAL_VALVE::VALVE_SHOTAT:
				name = "valve_shotat";
			case SEAL_VALVE::VALVE_ALIVE:
				name = "valve_alive";
			case SEAL_VALVE::VALVE_AWARE:
				name = "valve_aware";
			default:
				name = "error";
			}

			if (!strcmp(name, valve))
			{
				return seal_valve;
			}
		}

		if (!strcmp(valve, "valve_shot"))
		{
			return SEAL_VALVE::VALVE_SHOTAT;
		}
	}

	return SEAL_VALVE::VALVE_ERROR;
}

const char* CSealCtrlAi::get_valve(SEAL_VALVE valve)
{
	switch (valve)
	{
	case SEAL_VALVE::VALVE_HOLDFIRE:
		return "valve_holdfire";
	case SEAL_VALVE::VALVE_SHOTAT:
		return "valve_shotat";
	case SEAL_VALVE::VALVE_ALIVE:
		return "valve_alive";
	case SEAL_VALVE::VALVE_AWARE:
		return "valve_aware";
	default:
		return "error";
	}
}