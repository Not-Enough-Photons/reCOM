#pragma once
#include <string>
#include <vector>

static const char* TrimStr(char* src, char trimChar);
static void* CreateString(const char* str, const char* sourceFile, int line);

class CSTable
{
public:
	CSTable(size_t size, int count);
private:
	std::vector<const char*> m_StringTable;
};