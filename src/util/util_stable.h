#pragma once
#include <string>

namespace zdb
{
	class CSTable
	{
	public:
		CSTable(const char* name);
	private:
		std::string m_Name;
	};
}