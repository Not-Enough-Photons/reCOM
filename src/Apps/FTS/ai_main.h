#pragma once
#include "entity/ent_main.h"
#include "entity/seal/seal.h"

enum FIRE_TEAM
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

enum AI_LOOK
{
	type_00,
	type_01,
	type_02,
	type_03
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

enum GOAL_TYPE
{
	type_00,
	type_01,
	type_02,
	type_03,
	type_04
};

namespace sealai
{
	const char* get_state(AI_STATE state);
}

class CAiEvent
{
public:
	enum EVENT
	{
		type_00,
		type_01,
		type_02,
		type_03,
		type_04,
		type_05,
		type_06,
		type_07,
		type_08,
		type_09,
		type_10,
		type_11,
		type_12,
		type_13,
		type_14,
	};

	static CAiEvent* Create(CAiEvent* other);
	static CAiEvent* Acquire();

	static float GetEventRate(EVENT event);

	int aiBitMask;
	float expiration;
	float soundRadiusSqr;
	CPnt3D* source;
	CEntity* originator;
	int dummy;
};

class CAiParams
{

};

class CAiTimer
{
public:
	const float infinite = 0xBF800000;
};
