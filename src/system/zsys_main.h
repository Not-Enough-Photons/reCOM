#pragma once
#include <stdlib.h>
#include <cstring>
#include <cassert>

void InitSystemTuners();
void zSysMain();
void zSysReset();

void zAllocateAssert(bool condition, const char* sourceFile, int line);
void* zAllocateAlign(size_t alignment, size_t size, const char* sourceFile, int line);
void* zAllocateArray(int size, int count, const char* sourceFile, int line);
void* zAllocateString(const char* str, const char* sourceFile, int line);
void* zReAllocate(void* ptr, size_t size, const char* sourceFile, int line);
void* zAllocate(size_t size, const char* sourceFile, int line);
void* zAllocateInst(void* instance, const char* sourceFile, int line);

class CSched_Manager
{
public:
	static void Clear(const char* sched);
};