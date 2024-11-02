#pragma once
#include <string>
#include <vector>

class CSTable
{
public:
	CSTable(size_t size, int count);

	const char* CreateString(const char* str);
private:
	std::vector<const char*> m_StringTable;
};