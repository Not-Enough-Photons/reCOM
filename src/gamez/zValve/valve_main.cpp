#include "zvalve.h"

// #include "gamez/zAnim/zanim.h"

CValvePool valvePool;

CValve::CValve(const char* name, u32 value, VALVE_TYPE type)
{
	m_list.clear();
	
	m_name = NULL;
	m_name_pooled = false;
	m_pooled = false;
	m_value = value;
	m_type = (u32)VALVE_TYPE::VTYPE_NONE;

	FreeName();

	if (name)
	{
		m_name = zstrdup(name);
	}
}

bool CValve::Open(const char* name, VALVE_TYPE type)
{
	if (name)
	{
		CRdrFile* file = zrdr_read(name, NULL, 0);
		Parse(file, type);
		zrdr_free(file);
	}

	if (valvePool.empty())
	{
		valvePool.reserve(256);

		for (u32 i = 0; i < 256; i++)
		{
			CValve* valve = new CValve(NULL, 0, VALVE_TYPE::VTYPE_TEMP);
			valve->m_name_pooled = true;
			valve->m_pooled = true;
			valve->m_type = (u32)VALVE_TYPE::VTYPE_PERM;
			valve->m_value = 1;
			valvePool.insert(valvePool.end(), valve);
		}
	}
	
	return true;
}

bool CValve::Parse(_zrdr* reader, VALVE_TYPE type)
{
	CValve* valve = NULL;
	_zrdr* valves = zrdr_findtag(reader, "valves");

	if (valves)
	{
		s32 idx = 1;
		
		if (valves->array->integer > 1)
		{
			do
			{
				VALVE_STATE vstate;
				char* name = NULL;
				s32 value = 0;
				char* valve_type = NULL;
				
				_zrdr* node = &valves->array[idx];

				name = zrdr_findstring(node, "name");
				zrdr_findint(node, "value", &value, 1);
				valve_type = zrdr_findstring(node, "type");

				VALVE_TYPE rdr_valve_type = VALVE_TYPE::VTYPE_NONE;

				if (valve_type)
				{
					if (strcmp(valve_type, "PERM") == 0)
					{
						rdr_valve_type = VALVE_TYPE::VTYPE_PERM;
					}
					else if (strcmp(valve_type, "TEMP") == 0)
					{
						rdr_valve_type = VALVE_TYPE::VTYPE_TEMP;
					}
					else if (strcmp(valve_type, "PERSIST") == 0)
					{
						rdr_valve_type = VALVE_TYPE::VTYPE_PERSIST;
					}
				}

				if (!name)
				{
					valve = NULL;
				}
				else
				{
					valve = GetByName(name);
				}

				if (!valve)
				{
					valve = valvePool.Acquire(name, type);
					vstate = VALVE_STATE::VSTATE_DORMANT;

					if (value != 0)
					{
						vstate = VALVE_STATE::VSTATE_PERMANENT;
					}
					
					if (valve->m_value != value)
					{
						vstate = VALVE_STATE::VSTATE_TEMPORARY;
					}

					valve->m_value = value;

					if (vstate != VALVE_STATE::VSTATE_DORMANT)
					{
						// valve->MakeCallbacks(vstate);
					}

					m_list.insert(m_list.begin(), valve);
				}
				
				idx++;
			}
			while (idx < valves->array->integer);
		}
	}
	
	return true;
}

CValve* CValve::Create(const char* name, VALVE_TYPE type)
{
	CValve* valve = NULL;

	if (name == NULL)
	{
		return NULL;
	}

	for (auto it = m_list.begin(); it != m_list.end(); ++it)
	{
		CValve* curValve = *it;
		const char* valveName = curValve->m_name;

		if (valveName != NULL && strcmp(valveName, name) == 0)
		{
			valve = curValve;
		}
	}
	
	if (valve == NULL)
	{
		valve = valvePool.Acquire(name, type);
		m_list.insert(m_list.begin(), valve);
	}
	else
	{
		if (type == VALVE_TYPE::VTYPE_PERM && valve->m_type != (u32)VALVE_TYPE::VTYPE_PERSIST)
		{
			valve->m_type = (u32)VALVE_TYPE::VTYPE_PERM;
		}

		if (type == VALVE_TYPE::VTYPE_PERSIST)
		{
			valve->m_type = (u32)VALVE_TYPE::VTYPE_PERSIST;
		}
	}

	return valve;
}

CValve* CValve::Create(const char* name, s32 count, VALVE_TYPE type)
{
	return NULL;
}

CValve* CValve::GetByName(const char* name)
{
	if (name)
	{
		auto it = m_list.begin();
		while (it != m_list.end())
		{
			CValve* current = *it;

			if (strcmp(current->m_name, name) == 0)
			{
				return current;
			}
			
			++it;
		}
	}

	return NULL;
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

void CValve::FreeName()
{
	if (m_name_pooled)
	{
		if (m_name)
		{
			zfree(m_name);
		}

		m_name = NULL;
	}
	else
	{
		m_name = NULL;
	}

	m_name_pooled = false;
}

bool CValve::Set(s32 value)
{
	VALVE_STATE state;

	if (m_value != value && value != 0)
	{
		state = VALVE_STATE::VSTATE_DORMANT;
	}

	m_value = value;

	if (state != VALVE_STATE::VSTATE_DORMANT)
	{
		MakeCallbacks(state);
	}

	return state != VALVE_STATE::VSTATE_DORMANT;
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