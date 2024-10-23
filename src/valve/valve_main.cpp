#include "valve_main.h"

#include "anim/anim_main.h"

zanim_cmd_hdr* CValve::CmdParseCmp(zrdr* reader)
{

}

void CValve::RegisterCommands()
{
	ZAnim.AddCmd("VALVE", CmdParseCmp, NULL, CmdTickCmp, NULL);
}

CValve* CValve::GetByName(const char* name)
{

}

void CValve::SetName(const char* name)
{

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