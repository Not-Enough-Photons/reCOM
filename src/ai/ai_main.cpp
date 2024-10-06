#include <cstdint>
#include <iostream>
#include "ai_main.h"

enum AIState
{
	STATE_SLEEP,
	STATE_IDLE,
	STATE_HOLD,
	STATE_PATH,
	STATE_CREEP,
	STATE_SLIDE,
	STATE_FOLLOW,
	STATE_CLIMB,
	STATE_TEST,
	NUM_STATES
};

typedef struct AIParams
{
	float accuracy;
	float courage;
	float surrender;
	float stealth;
	float training;
	float target_delay;
	float target_discipline;
};

typedef struct AISensors
{
	float visual_range;
	float visual_fov;
	float visual_sens;
	float aware_decay;
	float thip_range;
	int respawn;
};

const char* GetTeamName(char param_1)
{
	if (param_1 == 31)
	{
		return "ALLIES";
	}
	else if (param_1 == 30)
	{
		return "ENEMIES";
	}
	else if (param_1 == 28)
	{
		return "HOSTAGE";
	}
	else if (param_1 == 29)
	{
		return "SUPPORT";
	}
	else if (param_1 == 27)
	{
		return "TURRETS";
	}
	else if (param_1 == 26)
	{
		return "NEUTRAL";
	}
	else if (param_1 == 18)
	{
		return "FRIENDLY";
	}
	else if (param_1 == 17)
	{
		return "ESCORTEE";
	}
	else if (param_1 == 3)
	{
		return "BRAVO";
	}
	else if (param_1 == 2)
	{
		return "ABLE";
	}
	else if (param_1 == 1)
	{
		return "FIRETEAM";
	}

	return "FT_UNKNOWN";
}

int SetParameter(long param_2, char* paramName, uint32_t* ptr, int32_t param_4)
{
	return 1;
}

unsigned int GetDebugAIState(long param_1)
{
	int iVar1;
	const char* name;
	int state;

	while (true)
	{
		if (param_1 == 0 || (8 < state))
		{
			return 1;
		}

		if ((state & 255) < 10)
		{
			switch (state)
			{
			case STATE_SLEEP:
				name = "sleep";
				break;
			case STATE_IDLE:
				name = "idle";
				break;
			case STATE_HOLD:
				name = "hold";
				break;
			case STATE_PATH:
				name = "path";
				break;
			case STATE_CREEP:
				name = "creep";
				break;
			case STATE_SLIDE:
				name = "slide";
				break;
			case STATE_FOLLOW:
				name = "follow";
				break;
			case STATE_CLIMB:
				name = "climb";
				break;
			case STATE_TEST:
				name = "test";
				break;
			default:
				name = "error";
			}
		}

		if (strcmp((char*)param_1, name))
		{
			break;
		}

		state++;
	}

	return state & 255;
}

void SetAIParameters(uint32_t* aiPtr, long param_2)
{
	AIParams aiParams;
	AISensors aiSensors;

	if (param_2 != 0)
	{
		if (SetParameter(param_2, "accuracy", aiPtr, 1))
		{

		}

		if (SetParameter(param_2, "courage", aiPtr, 1))
		{

		}

		if (SetParameter(param_2, "surrender", aiPtr, 1))
		{

		}

		if (SetParameter(param_2, "stealh", aiPtr, 1))
		{

		}

		if (SetParameter(param_2, "training", aiPtr, 1))
		{

		}

		if (SetParameter(param_2, "target_delay", aiPtr, 1))
		{

		}

		if (SetParameter(param_2, "target_discipline", aiPtr, 1))
		{

		}
	}
}