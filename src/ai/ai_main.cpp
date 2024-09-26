#include <cstdint>

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

int SetParameter(long param_2, char* paramName, uint32_t* ptr, int32_t param_4);
{
	return 1;
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

		if (SetParameter(param_2, "target_discipline", aiPtr, 1)
		{

		}
	}
}