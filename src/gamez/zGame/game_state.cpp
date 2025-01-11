#include "zgame.h"

std::vector<CGameStateChangeCmd*> m_pool;

CGameState* CGame::Switch(CGameState* state, u32 index)
{
	CGameState* currentState;

	if (state == NULL)
	{
		return NULL;
	}
	else
	{
		if (m_CurrentState < 16)
		{
			currentState = m_Stack[m_CurrentState];
		}
		else
		{
			currentState = NULL;
		}

		for (auto it = m_pool.begin(); it != m_pool.end(); it++)
		{
			CGameStateChangeCmd* stateChange = *it;

			if (!stateChange->m_active)
			{
				stateChange->m_type = 2;
				stateChange->m_toState = state;
				stateChange->m_toStateIdx = index;
			}
		}
	}

	return currentState;
}