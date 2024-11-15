#pragma once
#include <string>
#include <vector>

class CSTable
{
public:
	CSTable(size_t size, int count);
	~CSTable();

	const char* CreateString(const char* str);
private:
	std::vector<char*> m_strings;
	char* m_owner;
	int m_bytes;
	int m_reserve;
};