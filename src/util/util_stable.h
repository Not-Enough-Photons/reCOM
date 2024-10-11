#pragma once
#include <string>

namespace zdb
{
	static const char* TrimStr(char* src, char trimChar);
	static void* CreateString(const char* str, const char* sourceFile, int line);

	class CSTable
	{
	public:
		CSTable(const char* name);
	private:
		std::string m_Name;
	};
}