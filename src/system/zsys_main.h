#pragma once
#include <stdlib.h>
#include <cstring>
#include <cassert>

namespace zdb
{
	static void zAllocateAssert(bool condition, char* allocator);
	static void* zAllocateAlign(size_t alignment, size_t size, char* sourceFile, int line);
	static void* zAllocateArray(int size, int count, char* sourceFile, int line);
	static void* zAllocateString(const char* str, const char* sourceFile, int line);
	static void* zReAllocate(void* ptr, size_t size, char* sourceFile, int line);
	static void* zAllocate(size_t size, char* sourceFile, int line);
}