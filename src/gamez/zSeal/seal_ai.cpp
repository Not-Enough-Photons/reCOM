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