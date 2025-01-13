#include "zvalve.h"

// #include "gamez/zAnim/zanim.h"

CValvePool valvePool;

CValve* CValve::Create(const char* name, VALVE_TYPE type)
{
	CValve* valve = NULL;

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
		if (type == VALVE_TYPE::PERM && valve->m_type != (u32)VALVE_TYPE::PERSIST)
		{
			valve->m_type = (u32)VALVE_TYPE::PERM;
		}

		if (type == VALVE_TYPE::PERSIST)
		{
			valve->m_type = (u32)VALVE_TYPE::PERSIST;
		}
	}

	return valve;
}

void CValve::RegisterCommands()
{
	// ZAnim.AddCmd("VALVE", CmdParseCmp, NULL, CmdTickCmp, NULL);
}

void CValve::AssignName(const char* name)
{

}

void* CValve::AddCallback(size_t size, void(*callback)(CValve*, void*), void* buffer)
{
	m_callbacks.m_list.insert(m_callbacks.m_list.begin(), callback);
	return callback;
}

void CValve::DeleteCallbacks()
{
	for (auto it = m_callbacks.m_list.begin(); it != m_callbacks.m_list.end(); it++)
	{
		m_callbacks.m_list.erase(m_callbacks.m_list.begin());
	}
}

bool CValve::Set(s32 value)
{
	VALVE_STATE state;

	if (m_value != value && value != 0)
	{
		state = VALVE_STATE::IDLE;
	}

	m_value = value;

	if (state != VALVE_STATE::IDLE)
	{
		MakeCallbacks(state);
	}

	return state != VALVE_STATE::IDLE;
}

OP_TYPE CValve::ParseOperator(const char* op)
{
	s32 cmp = 0;
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