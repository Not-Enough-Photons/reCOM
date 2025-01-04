#include <stdio.h>

#include "zsys.h"

bool postinited = false;

void zSysPostInit()
{
	if (!postinited)
	{
		postinited = true;
	}
}

void zVid_Assert(bool condition, unsigned int mask, const char* file, int line)
{
	if (!condition)
	{
		// zSysFifoEnd();
		char buffer[256];
		sprintf(buffer, "A S S E R T: %s : %d", file, line);
		// theTerminal.Print(buffer, 256);
		// theTerminal.Render();
	}
}

void* operator new(size_t size)
{
	return __malloc(size);
}

void* __malloc(size_t size)
{
	void* p = malloc(size);
	zVid_Assert(size == 0 || p != NULL, INT_MAX, __FILE__, __LINE__);
	return p;
}

void* __calloc(size_t num, size_t size)
{
	size_t calc_size = num * size;
	void* p = malloc(calc_size);
	memset(p, 0, calc_size);
	zVid_Assert(calc_size == 0 || p != NULL, INT_MAX, __FILE__, __LINE__);
	return p;
}

void* __realloc(void* ptr, size_t new_size)
{
	void* p = realloc(ptr, new_size);
	zVid_Assert(new_size == 0 || p != NULL, INT_MAX, __FILE__, __LINE__);
	return p;
}

void* __memalign(size_t alignment, size_t size)
{
	void* p = _aligned_malloc(size, alignment);
	zVid_Assert(alignment == 0 || p != NULL, INT_MAX, __FILE__, __LINE__);
	return p;
}

char* __strdup(const char* str)
{
	size_t len = strlen(str);
	len++;
	char* p = (char*)malloc(len);
	strcpy(p, str);
	zVid_Assert(len == 0 || p != NULL, INT_MAX, __FILE__, __LINE__);
	return p;
}

void __free(void* block)
{
	free(block);
}