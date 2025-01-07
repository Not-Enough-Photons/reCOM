#include "util_stable.h"

CSTable::CSTable()
{

}

CSTable::CSTable(size_t size, size_t count)
{
	m_owner = true;
	m_buffer = NULL;
	m_bytes = 0;
	m_reserve = 0;

	if (size != 0)
	{
		m_reserve = size;
		m_buffer = (char*)malloc(size);
		reserve(count);
	}
}

CSTable::~CSTable()
{
	if (m_buffer != NULL)
	{
		for (auto it = begin(); it != end(); it++)
		{
			free(*it);
			*it = NULL;
		}
	}
	else
	{
		if (!m_owner)
		{
			free(m_buffer);
		}

		m_buffer = NULL;
		m_bytes = 0;
		m_reserve = 0;
	}

	m_reserve = 0;
	clear();
}

void CSTable::Destroy()
{

}

char* CSTable::CreateString(const char* str)
{
	char* out = NULL;
	char* string = NULL;

	if (str == NULL)
	{
		return NULL;
	}

	// Check if the string already exists in the table
	for (auto it = begin(); it != end(); it++)
	{
		string = *it;

		// String matches?
		if (strlen(string) != 0 && strlen(str) != 0 && strcmp(string, str) == 0)
		{
			// Assign to our output
			break;
		}

		string = NULL;
	}

	out = string;

	// String doesn't exist in the table
	if (string == NULL)
	{
		// Is a character buffer available?
		if (m_buffer == NULL)
		{
			// Duplicate the string and insert it
			char* dupstr = strdup(str);
			insert(begin(), dupstr);
		}
		// Are we the owner of all strings?
		else if (m_owner)
		{
			size_t length = strlen(str) + 1;

			// Do we have enough space in the vector?
			if (m_bytes + length <= m_reserve)
			{
				// We do, so copy the characters over
				out = m_buffer + m_bytes;
				memcpy(out, str, length);
				m_bytes += length;

				insert(begin(), out);
			}
		}
	}

	return out;
}

char* CSTable::FindString(const char* str)
{
	if (str != NULL)
	{
		for (auto it = begin(); it != end(); it++)
		{
			char* string = *it;

			// String matches?
			if (strlen(str) != 0 && strlen(string) != 0 && strcmp(string, str) == 0)
			{
				return string;
			}
		}
	}
}

void CSTable::LoadTable(void* buffer, size_t bytes, bool owner)
{
	int idx;
	size_t length;
	char* ptr;
	int table_length;
	unsigned int byte;

	byte = 0;
	m_buffer = static_cast<char*>(buffer);
	m_bytes = bytes;
	m_owner = owner;
	ptr = m_buffer;
	idx = 0;

	if (bytes != 0)
	{
		do
		{
			idx++;
			length = strlen(ptr);
			table_length = length + 1;
			ptr += table_length;
			byte += table_length;
		} while (byte < bytes);
	}

	resize(idx);
	ptr = m_buffer;
	byte = 0;
	idx = 0;

	if (bytes != 0)
	{
		do
		{
			this->data()[idx] = ptr;
			length = strlen(ptr);
			table_length = length + 1;
			ptr += table_length;
			byte += table_length;
			idx++;
		} while (byte < bytes);
	}
}

void CSTable::ReleaseBuffer(bool owner)
{
	if (owner && m_buffer != NULL)
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