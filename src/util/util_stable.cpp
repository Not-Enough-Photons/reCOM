#include "util\util_stable.h"
#include "system\zsys_main.h"

namespace zdb
{
	CSTable::CSTable(const char* name)
	{
		m_Name = name;
	}

	void* CreateString(const char* str, const char* sourceFile, int line)
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
			dst = reinterpret_cast<char*>(zAllocateString(str, sourceFile, line));
		}

		return dst;
	}
}