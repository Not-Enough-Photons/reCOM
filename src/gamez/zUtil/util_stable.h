#pragma once
#include <string>
#include <vector>

const char* TrimStr(char* src, char trimChar);
char* TrimUpTowards(char* src, char* match);
void* CreateString(const char* str, const char* sourceFile, int line);

class CSTable
{
public:
	CSTable(size_t size, int count);

	const char* CreateString(const char* str);
private:
	std::vector<const char*> m_StringTable;
};