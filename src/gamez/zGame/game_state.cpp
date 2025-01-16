#include "zgame.h"

std::vector<CGameStateChangeCmd*> m_pool;

CGameState* CGame::Switch(CGameState* state, u32 index)
{
	CGameState* currentState = NULL;
	CGameStateChangeCmd* command = NULL;

	if (state == NULL)
	{
		return NULL;
	}
	else
	{
		// Check if the current state is inside the queue
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

			// Is the state inactive in the pool?
			// If it is, use it
			if (!stateChange->m_active)
			{
				stateChange->m_type = 2;
				stateChange->m_toState = state;
				stateChange->m_toStateIdx = index;
				command = stateChange;
				break;
			}
		}

		if (command != NULL)
		{
			command->m_active = true;
			command->m_type = 2;
			command->m_toState = state;
			command->m_toStateIdx = index;
		}

		m_StateChangeQueue.push_back(command);

		// Dispatch event
		if (currentState != NULL)
		{
			currentState->OnPush();
		}

		state->Init();
	}

	return currentState;
}