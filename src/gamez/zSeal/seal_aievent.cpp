#include "zseal.h"
#include "gamez/zgame.h"

bool CSealCtrl::CreateAiEvent(CAiEvent::EVENT event, float expiration, float radius, bool flag, CPnt3D* position, int dummy)
{
	bool success = false;
	float dt = theMission.nextFrameDelta - timerMap[event];
	float oldDt = theMission.nextFrameDelta;
	float eventRate = CAiEvent::GetEventRate(event);

	if (eventRate < dt)
	{
		timerMap[event] = oldDt;
		CZSealBody* body = this->body;

		CAiEvent* aiEvent = CAiEvent::Acquire();
		aiEvent->aiBitMask = aiEvent->aiBitMask & (1 | event & 0x7fffU << 1);
		aiEvent->expiration = expiration;
		aiEvent->soundRadiusSqr = radius * radius;
		aiEvent->aiBitMask = aiEvent->aiBitMask & 0xfe | flag;
		if (!position)
		{
			// position = vtable function call here
		}

		aiEvent->source = position;
		aiEvent->originator = body->baseEntity;
		CAiEvent::Create(aiEvent);

		success = true;
	}

	return success;
}