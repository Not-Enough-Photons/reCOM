#pragma once
#include <cstring>

namespace zdb
{
	const int TWO_BYTES = 2;
	const int FOUR_BYTES = 4;
	const int EIGHT_BYTES = 8;

	typedef struct ZEntry
	{
		int designator;
		char padding1;
		int count;
		char padding2;
		int* next;
		char padding3;
	} entry_t;

	static int IterateEntry(int* pointer, const char* label, int iterations)
	{
		int nextEntryBase = 0;
		entry_t entry;

		entry.designator = *pointer;

		if (entry.designator != 4)
		{
			return 0;
		}

		for (entry.count = *(pointer + TWO_BYTES); nextEntryBase == 0 && iterations < entry.count; iterations++)
		{
			if (entry.designator == 4)
			{
				entry.count = *(pointer + TWO_BYTES);
			}

			int next = 0;
			if (iterations < entry.count)
			{
				// Get the designator value stored at address
				// Multiply by a multiple of 16 (8 in this case), considering alignment
				// if iterations is non-zero
				entry.next = (pointer + FOUR_BYTES) + iterations * EIGHT_BYTES;
			}

			if (*entry.next == 4)
			{
				// Recurse until we hit a root
				nextEntryBase = IterateEntry(entry.next, label, 0);
			}
			else if (*entry.next == 3 && strcmp(label, (char*)*entry.next + FOUR_BYTES))
			{
				nextEntryBase = (*entry.next + FOUR_BYTES) + (iterations + 1) * EIGHT_BYTES;
			}
		}

		return nextEntryBase;
	}

	static void Verify(char* first, char* second)
	{
		first++;
		while (true)
		{
			second++;
			char* ptr = first;

			if (first == '\0')
			{
				break;
			}

			char* ptr2 = second;

			if ((*(int*)ptr & *(int*)ptr2) == 0)
			{

			}
		}
	}

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