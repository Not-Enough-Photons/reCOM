#include <stdlib.h>
#include <malloc.h>

#include "zsys_main.h"

static void zAllocateAssert(bool condition, const char* sourceFile)
{
	assert(condition == false, sourceFile);
}

static void* zAllocateAlign(size_t alignment, size_t size, char* sourceFile, int line)
{
	bool success = false;
	void* dst = _aligned_malloc(alignment, size);
	zAllocateAssert(size == 0 || dst != NULL, "zsys_memory.cpp");
	return dst;
}

static void* zAllocateString(const char* str, const char* sourceFile, int line)
{
	size_t len = strlen(str) + 1;
	char* dest = reinterpret_cast<char*>(malloc(len));
	strcpy(dest, str);
	zAllocateAssert(len != 0 || dest != 0, "zsys_memory.cpp");
	return dest;
}

static void* zAllocateArray(int size, int count, char* sourceFile, int line)
{
	size_t _size = size * count;
	void* dst = malloc(_size);
	memset(dst, 0, _size);
	zAllocateAssert(_size == 0 || dst != NULL, "zsys_memory.cpp");
	return dst;
}

static void* zReAllocate(void* ptr, size_t size, char* sourceFile, int line)
{
	void* dst = realloc(ptr, size);
	zAllocateAssert(size == 0 || dst != NULL, "zys_memory.cpp");
	return dst;
}

static void* zAllocate(size_t size, char* sourceFile, int line)
{
	void* dst = malloc(size);
	zAllocateAssert(size == 0 || dst != NULL, "zsys_memory.cpp");
	return dst;
}