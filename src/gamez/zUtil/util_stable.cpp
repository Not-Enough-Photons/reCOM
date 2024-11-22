#include "util_stable.h"

CSTable::CSTable(size_t size, size_t count)
{
	m_buffer = NULL;
	m_bytes = 0;
	m_reserve = 0;

	if (size != 0)
	{
		m_reserve = size;
		m_buffer = reinterpret_cast<char*>(malloc(size));
		reserve(count);
	}
}

void CSTable::Destroy()
{
	if (m_buffer == NULL)
	{
		for (auto it = begin(); it != end(); it++)
		{
			free(&it);
			*it = NULL;
		}
	}
	else
	{
		if (m_can_free)
		{
			free(m_buffer);
		}

		m_buffer = NULL;
		m_bytes = 0;
	}

	m_reserve = 0;
	this->~CSTable();
}

const char* CSTable::CreateString(const char* str)
{
	if (str == NULL)
	{
		return NULL;
	}
}

const char* CSTable::FindString(const char* str)
{
	if (str == NULL)
	{
		return NULL;
	}

	for (auto it = begin(); it != end(); it++)
	{
		const char* string = *it;

		if (string == NULL)
		{
			continue;
		}

		if (strlen(str) != 0 
			&& strlen(string) != 0 
			&& strcmp(str, string) == 0)
		{
			return string;
		}
	}

	return NULL;
}

void CSTable::LoadTable(void* buffer, size_t bytes, bool canFree)
{
	int idx = 0;
	int length = 0;
	char* ptr;
	int table_length;
	unsigned int byte = 0;

	m_buffer = reinterpret_cast<char*>(buffer);
	ptr = m_buffer;
	m_bytes = bytes;
	m_can_free = canFree;

	if (bytes != 0)
	{
		do
		{
			idx++;
			length = strlen(m_buffer);
			table_length = length + 1;
			ptr += table_length;
			byte += table_length;
		} while (byte < bytes);
	}

	resize(idx);

	// why twice?
	if (bytes != 0)
	{
		do
		{
			idx++;
			length = strlen(m_buffer);
			table_length = length + 1;
			ptr += table_length;
			byte += table_length;
		} while (byte < bytes);
	}
}

void CSTable::ReleaseBuffer(bool freeBuffer)
{
	if (freeBuffer && m_buffer != NULL)
	{
		free(m_buffer);
	}

	m_buffer == NULL;
}

int CSTable::Relocate(char* buffer)
{
	if (size() == 0)
	{
		return 0;
	}

	char* src = m_buffer;
	int offset = buffer - src;

	memcpy(buffer, src, m_bytes);

	auto bufData = data();
	auto bufSize = bufData + size();

	while (bufData != bufSize)
	{
		bufData++;
	}

	return offset;
}