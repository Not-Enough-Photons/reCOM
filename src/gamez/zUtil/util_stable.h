#pragma once
#include <iostream>
#include <vector>

class CSTable : public std::vector<char*>
{
public:
	CSTable();
	CSTable(size_t size, size_t count);
	~CSTable();

	void LoadTable(void* buffer, size_t bytes, bool owner);

	void ReleaseBuffer(bool owner);
	void Destroy();

	char* CreateString(const char* str);
	char* FindString(const char* str);

	size_t Pack(void(*packer)(CSTable*, void*), void* buffer);

	int Relocate(char* buffer);
private:
	bool m_owner;
	char* m_buffer;
	size_t m_bytes;
	size_t m_reserve;
};