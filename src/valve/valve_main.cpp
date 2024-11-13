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
			const char* valveName = curValve->name;

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
		if (type == PERM && valve->type != PERSIST)
		{
			valve->type = PERM;
		}

		if (type == PERSIST)
		{
			valve->type = PERSIST;
		}
	}

	return valve;
}

bool CValve::Parse(CRdrFile* file, VALVE_TYPE type)
{
	_zrdr* rootTag = zrdr_findtag(file, "valves");

	if (rootTag != NULL)
	{
		int count = cast_rdr_int(rootTag->value->value);
	}
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