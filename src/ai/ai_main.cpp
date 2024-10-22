#include <cstdint>
#include <iostream>
#include "ai_main.h"

const char* sealai::get_state(AI_STATE state)
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
		str = "hash";
		break;
	default:
		str = "undef";
	}
	return str;
}

CAiState* CAiState::Create(AI_STATE state)
{
	CAiState* aiState;

	switch (state)
	{
	case STATE_UNKNOWN:
		break;
	case STATE_SCRIPT:
		aiState = new CAiSScript();
		aiState->Reset(STATE_SCRIPT);
		break;
	case STATE_HOLD:
		aiState = new CAiSHold();
		aiState->Reset(STATE_HOLD);
		break;
	case STATE_AVOID:
		aiState = new CAiSAvoid();
		aiState->Reset(STATE_AVOID);
		break;
	case STATE_DEPLOY:
		aiState = new CAiSDeploy();
		aiState->Reset(STATE_DEPLOY);
		break;
	case STATE_LASING:
		break;
	case STATE_SURRENDER:
		aiState = new CAiSSurrender();
		aiState->Reset(STATE_SURRENDER);
		break;
	case STATE_RESTRAINED:
		aiState = new CAiSRestrained();
		aiState->Reset(STATE_RESTRAINED);
		break;
	case STATE_GOTO:
		aiState = new CAiSGoto();
		aiState->Reset(STATE_GOTO);
		break;
	case STATE_FOLLOW:
		aiState = new CAiSFollow();
		aiState->Reset(STATE_FOLLOW);
		break;
	case STATE_BREACH:
		aiState = new CAiSBreach();
		aiState->Reset(STATE_BREACH);
		break;
	case STATE_ACTION:
		aiState = new CAiSAction();
		aiState->Reset(STATE_ACTION);
		break;
	case STATE_PURSUE:
		aiState = new CAiSPursue();
		aiState->Reset(STATE_PURSUE);
		break;
	case STATE_ANIMATE:
		aiState = new CAiSAnimate();
		aiState->Reset(STATE_ANIMATE);
		break;
	case STATE_CQB:
		aiState = new CAiSCQBAttack();
		aiState->Reset(STATE_CQB);
		break;
	case STATE_FLEE:
		aiState = new CAiSFlee();
		aiState->Reset(STATE_FLEE);
		break;
	case STATE_PATHRECO:
		aiState = new CAiSPathRecover();
		aiState->Reset(STATE_PATHRECO);
		break;
	case STATE_RESCUED:
		aiState = new CAiSRescued();
		break;
	case STATE_SUSPENDED:
		aiState = new CAiSSuspended();
		break;
	case STATE_SHOTAT:
		aiState = new CAiSShotAt();
		break;
	case STATE_RELOAD:
		// aiState = new CAiSReload();
		break;
	case STATE_NOAMMO:
		aiState = new CAiSNoAmmo();
		break;
	case STATE_PICKUP:
		// aiState = new CAiSPickup();

		break;
	case STATE_HOSTAGE:
		aiState = new CAiSHostage();
		break;
	case STATE_CORPSE:
		// aiState = new CAiSCorpse();

		break;
	case STATE_EVENT:
		aiState = new CAiSEvent();
		break;
	case STATE_TARGETING:
		aiState = new CAiSTarget();
		break;
	case STATE_GRENADE:
		aiState = new CAiSGrenade();
		break;
	case STATE_STUNNED:
		// aiState = new CAiSStunned();
		break;
	case STATE_RUSH:
		aiState = new CAiSRush();
		break;
	default:
		break;
	}
}