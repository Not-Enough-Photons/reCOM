#include "zanim.h"

bool CZAnimMain::m_LoadFromZAR = false;

bool CZAnimMain::SplitName(const char* name, char** splitname)
{
	bool split_success = false;
	char* haystack = NULL;

	if (!name)
	{
		*splitname = NULL;
		split_success = false;
	}
	else
	{
		char* separator = zstrdup(strstr(name, "::"));

		if (!separator)
		{
			*splitname = zstrdup(name);
		}
		else
		{
			haystack = zstrdup(name);
			separator = strstr(haystack, "::");
			*separator = '\0';
			*splitname = separator + 2;
		}

		split_success = haystack != NULL;
	}

	return split_success;
}

u32 CZAnimMain::AddCmd(const char* name,
	_zanim_cmd_hdr* (*parser)(_zrdr*),
	void(*begin)(_zanim_cmd_hdr*),
	bool(*tick)(_zanim_cmd_hdr*, float*),
	void(*end)(_zanim_cmd_hdr*))
{
	char* anim_name = NULL;
	
	bool split_success = SplitName(name, &anim_name);
	
	return 0;
}