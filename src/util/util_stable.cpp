#include "util\util_stable.h"
#include "system\zsys_main.h"

CSTable::CSTable(size_t size, int count)
{
	if (size != 0)
	{
		zAllocate(size, "util_stable.cpp", 54);
		m_StringTable.reserve(count);
	}
}

static const char* TrimStr(char* src, char trimChar)
{
	char c;
	char* p;

	p = 0;
	c = *src;

	while (c != '\0')
	{
		if (c == trimChar)
		{
			p = src;
		}

		src++;
		c = *src;
	}

	if (trimChar != '\0')
	{
		src = p;
	}

	return src;
}

static void* CreateString(const char* str, const char* sourceFile, int line)
{
	char* dst = NULL;
	size_t size = strlen(str);
	int pad = size + 4;

	if (size < 1U < 25)
	{
		if (pad < 0)
		{
			pad = size + 7;
		}

		// dst = reinterpret_cast<char*>(GlobalAllocate((pad >> 2) << 2));
		if (dst != 0)
		{
			strcpy(dst, str);
		}
	}
	else
	{
		// dst = reinterpret_cast<char*>(zAllocateString(str, sourceFile, line));
	}

	return dst;
}