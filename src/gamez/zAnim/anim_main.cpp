#include "zanim.h"

unsigned int CZAnimMain::AddCmd(const char* name,
	_zanim_cmd_hdr* (*parser)(_zrdr*),
	void(*begin)(_zanim_cmd_hdr*),
	bool(*tick)(_zanim_cmd_hdr*, float*),
	void(*end)(_zanim_cmd_hdr*))
{
	return 0;
}