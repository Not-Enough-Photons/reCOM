#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

#include "zsys_main.h"

void zAllocateAssert(bool condition, const char* sourceFile, int line)
{
	if (!condition)
	{
		printf("Assertion failed in %s at line %d - Memory allocation failed", sourceFile, line);
		abort();
	}
}

void* zAllocateAlign(size_t alignment, size_t size, const char* sourceFile, int line)
{
	bool success = false;
	void* dst = _aligned_malloc(alignment, size);
	zAllocateAssert(size == 0 || dst != NULL, sourceFile, line);
	return dst;
}

void* zAllocateString(const char* str, const char* sourceFile, int line)
{
	size_t len = strlen(str) + 1;
	char* dest = reinterpret_cast<char*>(malloc(len));
	strcpy(dest, str);
	zAllocateAssert(len == 0 || dest != 0, sourceFile, line);
	return dest;
}

void* zAllocateArray(int size, int count, const char* sourceFile, int line)
{
	size_t _size = size * count;
	void* dst = malloc(_size);
	memset(dst, 0, _size);
	zAllocateAssert(_size == 0 || dst != NULL, sourceFile, line);
	return dst;
}

void* zReAllocate(void* ptr, size_t size, const char* sourceFile, int line)
{
	void* dst = realloc(ptr, size);
	zAllocateAssert(size == 0 || dst != NULL, sourceFile, line);
	return dst;
}

void* zAllocate(size_t size, const char* sourceFile, int line)
{
	void* dst = malloc(size);
	zAllocateAssert(size == 0 || dst != NULL, sourceFile, line);
	return dst;
}