#include "zgame.h"

#include "gamez/zNetwork/znet.h"
#include "gamez/zUtil/zutil.h"
#include "gamez/zVideo/zvid.h"

CGame theGame;

void CGame::StartPlay()
{
	m_Active = true;
	Switch(m_InitialState, 0);
}

bool CGame::Tick(f32 dT)
{
	CGameState* state = NULL;

	theNetwork.zNetUpdate();
	theVoice.PreTick();
	// CConsole::m_console->Tick();

	if (m_CurrentState < 16)
	{
		state = m_Stack[m_CurrentState];
	}
	else
	{
		state = NULL;
	}

	if (m_Active)
	{
		if (m_StateChangeQueue.size() == 0)
		{
			if (state != NULL)
			{
				state->Tick(dT);
			}
		}

		theVoice.Tick(dT);
	}

	return false;
}