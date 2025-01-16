#include "zgame.h"

#include "gamez/zRender/zrender.h"
#include "gamez/zNetwork/znet.h"
#include "gamez/zUtil/zutil.h"
#include "gamez/zVideo/zvid.h"

CGame theGame;

CGame::CGame()
{
	m_Active = false;
	m_InitialState = new CTestState();
	m_CurrentState = 0;
	m_MinIdlePeriod = 100;
	m_TestVariable = NULL;
	memset(m_Stack, 0, 64);
	m_pad = 0;
	m_maxtick = 0;
}

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
		//if (m_StateChangeQueue.size() == 0)
		//{
		//	if (state != NULL)
		//	{
		//		state->Tick(dT);
		//	}
		//}

		m_InitialState->Tick(dT);

		theVoice.Tick(dT);
	}

	return false;
}

void CGameMenu::DrawForeplane()
{
	thePipe.m_node = m_pForeplaneNode;
	// Enable orthographic view for UI layer
	thePipe.m_simpletrans = true;
	thePipe.RenderUINode(m_pForeplaneNode);
	// Disable orthographic view for UI layer
	thePipe.m_simpletrans = false;
}