#include "zsys_main.h"

namespace zdb
{
	static void zAllocateAssert(bool condition, const char* sourceFile)
	{
		assert(condition == false, sourceFile);
	}

	static void* zAllocateAlign(size_t alignment, size_t size, char* sourceFile, int line)
	{
		return nullptr;
	}

	static void* zAllocateString(char* str, char* sourceFile, int line)
	{
		size_t len = strlen(str) + 1;
		char* dest = reinterpret_cast<char*>(malloc(len));
		strcpy(dest, str);
		zAllocateAssert(len != 0 || dest != 0, "zsys_memory.cpp");
	}

	static void* zAllocateArray(int param_1, int param_2, char* sourceFile, int line)
	{
		size_t size = param_1 * param_2;
		void* dst = malloc(size);
		memset(dst, 0, size);
		zAllocateAssert(size == 0 || dst != NULL, "zsys_memory.cpp");
		return dst;
	}

	static void* zReAllocate(void* ptr, size_t size, char* sourceFile, int line)
	{
		void* dst = realloc(ptr, size);
		zAllocateAssert(size == 0 || dst != NULL, "zys_memory.cpp");
		return dst;
	}

	void* zAllocate(size_t size, char* sourceFile, int line)
	{
		void* dst = malloc(size);
		zAllocateAssert(size == 0 || dst != NULL, "zsys_memory.cpp");
		return dst;
	}
}