#include "znet.h"

bool g_status = false;

CZNetVoice theVoice;

void PTT_HeartbeatPrepare()
{

}

bool CZNetVoice::PreTick()
{
	if (theNetwork.m_bNetwork && m_isOn)
	{
		PTT_HeartbeatPrepare();
	}

	return false;
}

bool CZNetVoice::Tick(f32 dT)
{
	bool status = false;

	if (theNetwork.m_bNetwork && m_isOn)
	{
		// RotateReadyThreadQueue(5);

		if (g_status != false)
		{
			g_status = false;
		}

		// s32 heartbeat = PTT_Heartbeat(1000000);
		// m_timeTaken = heartbeat;
		status = false;
	}
	else
	{
		status = true;
	}

	return status;
}