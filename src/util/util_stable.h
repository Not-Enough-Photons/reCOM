#pragma once
#include <string>

namespace zdb
{
	static void* CreateString(const char* str, const char* sourceFile, int line);

	class CSTable
	{
	public:
		CSTable(const char* name);
	private:
		std::string m_Name;
	};
}