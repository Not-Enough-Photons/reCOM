#pragma once
#include <iostream>

namespace zdb
{
	class CIO
	{

	};

	class CFileIO : public CIO
	{
	public:
		CFileIO();
	private:
		int m_Data;
	};

	class CBufferIO : public CFileIO
	{

	};

	class CRdrIO : public CFileIO
	{
	public:
		int FUN_0031f5f8(char* param_1, char* param_2);
		int UnknownFileIOFunction(int* param_1, char* label);
		int GetArchiveOffset(int* archivePtr);
		void ReadString(void* archive, char* label, char* buf, size_t maxLength);
	};

	class CRdrArchive : public CRdrIO
	{

	};
}
