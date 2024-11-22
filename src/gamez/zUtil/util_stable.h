#pragma once
#include <string>
#include <vector>

class CSTable : std::vector<const char*>
{
public:
	CSTable(size_t reserve, size_t count);
	~CSTable();

	void Destroy();

	const char* CreateString(const char* str);
	const char* FindString(const char* str);

	void LoadTable(void* buffer, size_t bytes, bool canFree);
	void ReleaseBuffer(bool freeBuffer);
	int Relocate(char* buffer);
private:
	bool m_can_free;
	unsigned char m_owner;
	char* m_buffer;
	unsigned int m_bytes;
	size_t m_reserve;
};