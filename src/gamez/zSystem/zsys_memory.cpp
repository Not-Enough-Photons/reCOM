#include <stdio.h>

#include "zsys.h"

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
		zSysFifoEnd();
		char buffer[256];
		sprintf(buffer, "A S S E R T: %s : %d", file, line);
		theTerminal.Print(buffer, 256);
		theTerminal.Render();
	}
}

void* operator new(size_t size)
{
	void* p = malloc(size);
	zVid_Assert(size == 0 || p != NULL, 0x800000ff, "zsys_memory.cpp", 20);
	return p;
}

void* malloc(size_t size)
{
	void* p = malloc(size);
	zVid_Assert(size == 0 || p != NULL, 0x800000ff, "zsys_memory.cpp", 27);
}

void* calloc(size_t num, size_t size)
{
	size_t calc_size = num * size;
	void* p = malloc(calc_size);
	memset(p, 0, calc_size);
	zVid_Assert(calc_size == 0 || p != NULL, 0x800000ff, "zsys_memory.cpp", 35);
}

void* realloc(void* ptr, size_t new_size)
{
	void* p = realloc(ptr, new_size);
	zVid_Assert(new_size == 0 || p != NULL, 0x800000ff, "zsys_memory.cpp", 41);
	return p;
}

void* memalign(size_t alignment, size_t size)
{
	void* p = _aligned_malloc(size, alignment);
	zVid_Assert(alignment == 0 || p != NULL, 0x800000ff, "zsys_memory.cpp", 48);
	return p;
}

char* strdup(const char* str1)
{
	size_t len = strlen(str1);
	len++;
	char* p = (char*)malloc(len);
	strcpy(p, str1);
	zVid_Assert(len == 0 || p != NULL, 0x800000ff, "zsys_memory.cpp", 51);
	return p;
}