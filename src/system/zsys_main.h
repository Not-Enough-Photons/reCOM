#pragma once
#include <stdlib.h>
#include <cstring>
#include <cassert>

constexpr void BIT_MASK(size_t size, char* buffer)
{
    int i = 0;
    char* pbVar1 = 0;
	do
	{
        if ((buffer != '\0') && (i = 0, 0 < size))
        {
            if (8 < size)
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
                } while (i < size - 8);
            }

            for (; i < size; i++)
            {
                *(buffer + i) = ~*(buffer + i);
            }
        }
	} while (pbVar1 < )
}

static void zAllocateAssert(bool condition, char* allocator);
static void* zAllocateAlign(size_t alignment, size_t size, char* sourceFile, int line);
static void* zAllocateArray(int size, int count, char* sourceFile, int line);
static void* zAllocateString(const char* str, const char* sourceFile, int line);
static void* zReAllocate(void* ptr, size_t size, char* sourceFile, int line);
static void* zAllocate(size_t size, char* sourceFile, int line);