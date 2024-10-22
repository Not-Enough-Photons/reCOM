#pragma once
enum FireTeam
{
	FT_UNKNOWN,
	FIRETEAM,
	ABLE,
	BRAVO,
	ESCORTEE,
	FRIENDLY,
	NEUTRAL,
	TURRETS,
	SUPPORT,
	HOSTAGE,
	ENEMIES,
	ALLIES
};

enum FT_COMMAND
{
	CMD_UNKNOWN,
	CMD_ACTION,
	CMD_DEPLOY,
	CMD_FIREATWILL,
	CMD_FOLLOW,
	CMD_HOLDPOS,
	CMD_HOLDFIRE,
	CMD_REGROUP,
	CMD_ESCORT,
	CMD_RUNTO,
	CMD_MOVETO,
	CMD_STEALTHTO,
	CMD_ATTACKTO,
	CMD_LEADTO,
	CMD_COVERTARGET,
	CMD_LASETARGET,
	CMD_BREACH,
	CMD_GETDOWN,
	CMD_PULLOUT,
	CMD_OVERWATCH,
	CMD_SUPPORT,
	CMD_EXTRACT,
	CMD_CLEARAREA,
	CMD_RESTRAIN,
	CMD_REMOVEKILLS,
	CMD_AWAKE,
	CMD_SLEEP,
	CMD_AMBUSH
};

enum AI_STATE
{
	STATE_UNKNOWN,
	STATE_SCRIPT,
	STATE_HOLD,
	STATE_AVOID,
	STATE_DEPLOY,
	STATE_LASING,
	STATE_SURRENDER,
	STATE_RESTRAINED,
	STATE_GOTO,
	STATE_FOLLOW,
	STATE_BREACH,
	STATE_ACTION,
	STATE_PURSUE,
	STATE_ANIMATE,
	STATE_CQB,
	STATE_FLEE,
	STATE_PATHRECO,
	STATE_RESCUED,
	STATE_SUSPENDED,
	STATE_SHOTAT,
	STATE_RELOAD,
	STATE_NOAMMO,
	STATE_PICKUP,
	STATE_HOSTAGE,
	STATE_CORPSE,
	STATE_EVENT,
	STATE_TARGETING,
	STATE_GRENADE,
	STATE_STUNNED,
	STATE_RUSH
};

namespace sealai
{
	const char* get_state(AI_STATE state);
}

class CAiParams
{

};

class CAiState
{
public:
	CAiState();
	~CAiState();

	static CAiState* Create(AI_STATE state);

	void Reset(AI_STATE state);
};

class CAiSScript : public CAiState
{

};

class CAiSHold : public CAiState
{

};

class CAiSAvoid : public CAiState
{

};

class CAiSDeploy : public CAiState
{

};

class CAiSSurrender : public CAiState
{

};

class CAiSRestrained : public CAiState
{

};

class CAiSUseVehicle : public CAiState
{

};

class CAiSGoto : public CAiState
{

};

class CAiSFollow : public CAiState
{

};

class CAiSBreach : public CAiState
{

};

class CAiSAction : public CAiState
{

};

class CAiSPursue : public CAiState
{

};

class CAiSAnimate : public CAiState
{

};

class CAiSCQBAttack : public CAiState
{

};

class CAiSFlee : public CAiState
{

};

class CAiSPathRecover : public CAiState
{

};

class CAiSRescued : public CAiState
{

};

class CAiSSuspended : public CAiState
{

};

class CAiSShotAt : public CAiState
{

};

class CAiSNoAmmo : public CAiState
{

};

class CAiSHostage : public CAiState
{

};

class CAiSPlan : public CAiState
{

};

class CAiSEvent : public CAiState
{

};

class CAiSTarget : public CAiState
{

};

class CAiSGrenade : public CAiState
{

};

class CAiSStunResponse : public CAiState
{

};

class CAiSRush : public CAiState
{

};

class CAiPlanner
{

};

class CBasicPlanner : public CAiPlanner
{

};

class CStealthPlanner : public CAiPlanner
{

};

class CRestrainedPlanner : public CAiPlanner
{

};