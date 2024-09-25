#pragma once
namespace zdb
{
	static void FlipBytes(char* src, char* buffer, int offset)
	{
		int i;
		char* pbVar1;

		if ((src != '\0') && (i = 0, 0 < offset))
		{
			if (8 < offset)
			{
				do
				{
					pbVar1 = buffer + i;
					i += 8;
					*pbVar1 = ~*pbVar1;
					pbVar1[1] = ~pbVar1[1];
					pbVar1[2] = ~pbVar1[2];
					pbVar1[3] = ~pbVar1[3];
					pbVar1[4] = ~pbVar1[4];
					pbVar1[5] = ~pbVar1[5];
					pbVar1[6] = ~pbVar1[6];
					pbVar1[7] = ~pbVar1[7];
				} while (i < offset - 8);
			}

			for (; i < offset; i++)
			{
				*(buffer + i) = ~*(buffer + i);
			}
		}
	}

	static char* TrimUpTowards(char* src, char* match)
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
}