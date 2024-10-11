#include "zrdr_main.h"

CFileIO::CFileIO()
{
	m_Data = 0xFFFFFFF;
}

int CRdrIO::FUN_0031f5f8(char* param_1, char* param_2)
{
	char* baseReaderName = param_1;

	if (baseReaderName == '\0')
	{
		return 0;
	}
}

int CRdrIO::UnknownFileIOFunction(int* ptr, char* label)
{
	// some of the worst code i have ever written
	if (*(ptr + 4) == 0)
	{
		return 0;
	}

	int* ptrTable = nullptr;
	int* ptrTableEnd = ptrTable + *(ptr + 4);

	for (; ptrTable != ptrTableEnd; ptrTable++)
	{
		if (*(int*)(*ptrTable + 16) == -1)
		{
			break;
		}

		if (FUN_0031f5f8((char*)ptr, *(char**)(*ptrTable + 12)))
		{
			break;
		}
	}

	if (ptrTable == nullptr)
	{
		return 0;
	}

	if (ptrTable != (int*)(*(int*)ptr + 8) + *(int*)(ptr + 4) * 4)
	{
		return *ptrTable;
	}

	return 0;
}

int CRdrIO::GetArchiveOffset(int* archivePtr)
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

void CRdrIO::ReadString(void* archive, char* label, char* buf, size_t maxLength)
{
	int offset = GetArchiveOffset((int*)archive);
	char* cVar = '\0';
}