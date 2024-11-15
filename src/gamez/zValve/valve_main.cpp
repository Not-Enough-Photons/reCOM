#include "valve_main.h"

#include "gamez/zAnim/anim_main.h"

CValve* CValve::Create(const char* name, VALVE_TYPE type)
{
	CValve* valve;

	if (name == NULL)
	{
		return NULL;
	}
	else
	{
		for (auto it = m_list.begin(); it != m_list.end(); it++)
		{
			CValve* curValve = *it;
			const char* valveName = curValve->m_name;

			if (valveName != NULL && strcmp(valveName, name) == 0)
			{
				valve = curValve;
			}
		}
	}

	if (valve == NULL)
	{
		valve = valvePool.Acquire(name, type);
		m_list.insert(m_list.begin(), valve);
	}
	else
	{
		if (type == PERM && valve->m_type != PERSIST)
		{
			valve->m_type = PERM;
		}

		if (type == PERSIST)
		{
			valve->m_type = PERSIST;
		}
	}

	return valve;
}

void CValve::AssignName(const char* name)
{

}

void* CValve::AddCallback(int size, void(*callback)(CValve*, void*), void* buffer)
{
	m_callbacks.m_list.insert(m_callbacks.m_list.begin(), callback);
}

void CValve::DeleteCallbacks()
{
	for (auto it = m_callbacks.m_list.begin(); it != m_callbacks.m_list.end(); it++)
	{
		// TODO:
		// can't delete function pointers....
	}
}

bool CValve::Set(int value)
{
	VALVE_STATE state;

	if (m_value != value && value != 0)
	{
		state = VALVE_STATE::IDLE;
	}

	m_value = value;

	if (state != VALVE_STATE::NONE)
	{
		MakeCallbacks(state);
	}

	return state != VALVE_STATE::NONE;
}

OP_TYPE CValve::ParseOperator(const char* op)
{
	int cmp = 0;
	OP_TYPE operation = OP_NONE;

	if (op != 0)
	{
		if (strcmp(op, "==") == 0)
		{
			operation = OP_CMP_EQUAL;
		}
		else if (strcmp(op, "!="))
		{
			operation = OP_CMP_NOTEQUAL;
		}
		else if (strcmp(op, ">="))
		{
			operation = OP_CMP_GTHANEQ;
		}
		else if (strcmp(op, "<="))
		{
			operation = OP_CMP_LTHANEQ;
		}
		else if (strcmp(op, ">"))
		{
			operation = OP_CMP_GTHAN;
		}
		else if (strcmp(op, "<"))
		{
			operation = OP_CMP_LTHAN;
		}
		else if (strcmp(op, "="))
		{
			operation = OP_EQUAL;
		}
		else if (strcmp(op, "-="))
		{
			operation = OP_DECREMENT;
		}
		else if (strcmp(op, "+="))
		{
			operation = OP_INCREMENT;
		}
	}

	return operation;
}