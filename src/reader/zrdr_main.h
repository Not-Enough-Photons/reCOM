#pragma once

namespace zdb
{
	class CIO
	{

	};

	class CFileIO : public CIO
	{

	};

	class CBufferIO : public CFileIO
	{

	};

	class CRdrIO : public CFileIO
	{
	public:
		int UnknownFileIOFunction(int* param_1, char* label);
		int GetArchiveOffset(int* archivePtr);
		void ReadString(void* archive, char* label, char* buf, size_t maxLength);
	};
}
