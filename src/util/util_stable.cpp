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

const char* TrimStr(char* src, char trimChar)
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

char* TrimUpTowards(char* src, char* match)
{
    if (*src == '\0')
    {
        char* terminator = '\0';

        if (*match == '\0')
        {
            terminator = src;
        }

        return terminator;
    }

    while (true)
    {
        // hit a null terminator
        // return the character buffer
        if (*match == '\0')
        {
            return src;
        }

        // match landed on our first character
        if (*match == *src)
        {
            int next = 1;

            while (true)
            {
                // next character is a null terminator?
                if (match[next] == '\0')
                {
                    return src;
                }

                // not our target character in the target string, 
                // ignore and break out of this loop
                if (match[next] != src[next])
                {
                    break;
                }

                next++;
            }
        }

        src++;
        if (*src == '\0')
        {
            break;
        }
    }

    return '\0';
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
		// dst = reinterpret_cast<char*>(zAllocateString(str, sourceFile, line));
	}

	return dst;
}