#include "zanim.h"

bool CZAnimMain::m_LoadFromZAR = false;

u32 CZAnimMain::AddCmd(const char* name,
	_zanim_cmd_hdr* (*parser)(_zrdr*),
	void(*begin)(_zanim_cmd_hdr*),
	bool(*tick)(_zanim_cmd_hdr*, float*),
	void(*end)(_zanim_cmd_hdr*))
{
	return 0;
}