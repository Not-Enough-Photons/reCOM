#include "zai.h"

float CAiEvent::GetEventRate(EVENT event)
{
	float rate = 0.0f;

	switch (event)
	{
	case AIE_UNKNOWN:
	case AIE_GENERIC:
	case AIE_POINT:
	case AIE_ENTITY:
	case AIE_VOICE:
	case AIE_WEPHIT:
	case AIE_CORPSE:
	case AIE_DOOR:
	case AIE_WEPFIRE:
	case AIE_EXPLOSION:
	case AIE_SURRENDER:
	case AIE_HELPATTACK:
	case AIE_ALARM:
		break;
	case AIE_GETDOWN:
		rate = 5.0f;
	}

	return rate;
}