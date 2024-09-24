#include "zrdr_main.h"

int zdb::CRdrIO::UnknownFileIOFunction(int* ptr, char* label)
{
	// some of the worst code i have ever written
	if (*(ptr + 4) == 0)
	{
		return 0;
	}

	int* ptrIndex = nullptr;
	int* ptrArray = ptrIndex + *(ptr + 4);

	for (; ptrIndex != ptrArray; ptrIndex++)
	{
		if (*(int*)(*ptrIndex + 16) == -1)
		{
			break;
		}

		// FUN_0031f5f8(char* param_1, char* param_2);
	}

	if (ptrIndex == nullptr)
	{
		return 0;
	}

	if (ptrIndex != (int*)(*(int*)ptr + 8) + *(int*)(ptr + 4) * 4)
	{
		return *ptrIndex;
	}

	return 0;
}

int zdb::CRdrIO::GetArchiveOffset(int* archivePtr)
{
	int offset = 0;

	if (*(archivePtr + 8) != 0)
	{
		// will need to look at that mips asm for this...
		// bottom is implemented though
	}
	else
	{
		offset = *(int*)(archivePtr + 12) - 4;
	}

	return offset;
}

void zdb::CRdrIO::ReadString(void* archive, char* label, char* buf, size_t maxLength)
{
	int offset = GetArchiveOffset((int*)archive);
	char* cVar = '\0';
}