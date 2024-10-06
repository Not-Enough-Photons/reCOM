#include <cstdint>
#include <iostream>

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