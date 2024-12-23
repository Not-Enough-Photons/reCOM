#include <sys/stat.h>

#include "util_systemio.h"

size_t CIO::fwrite(const char* buf)
{
	size_t size = 0;

	if (buf == NULL)
	{
		size = 0;
	}
	else
	{
		size = strlen(buf);
	}

	size_t bytesWritten = fwrite(&size, 4);

	if (buf != NULL)
	{
		size_t bufBytesWritten = fwrite(buf, size);
		bytesWritten += bufBytesWritten;
	}

	return bytesWritten;
}

CFileIO::CFileIO()
{
	m_file = NULL;
	m_mode = 0;
	m_filesize = 0;
	m_cd = NULL;
}

CFileIO::CFileIO(const CFileIO& other)
{
	m_file = NULL;
	m_filesize = other.m_filesize;
	m_file = other.m_file;
	m_mode = other.m_mode;
	m_cd = NULL;
}

bool CFileIO::Open(const char* file)
{
	m_file = (int)std::fopen(file, "rb");;

	if (m_file != NULL)
	{
		size_t filesize = std::fseek((FILE*)m_file, 0, SEEK_END);
		m_filesize = filesize;
		std::fseek((FILE*)m_file, 0, SEEK_SET);
	}

	return m_file != NULL;
}

void CFileIO::Close()
{
	bool open = m_file != NULL;

	if (open)
	{
		std::fclose((FILE*)m_file);
		m_file = NULL;
	}
}

void CFileIO::Release()
{
	m_file = NULL;
}

unsigned int CFileIO::GetMode() const
{
	return m_mode;
}

size_t CFileIO::GetSize() const
{
	return m_filesize;
}

bool CFileIO::IsOpen() const
{
	return -1 < m_file;
}

size_t CFileIO::fread(void* buf, size_t size)
{
	if (size == 0)
	{
		return 0;
	}
	else
	{
		return std::fread(buf, 1, size, (FILE*)m_file);
	}

	return 0;
}

size_t CFileIO::fread(int offset, void** buf)
{
	*buf = NULL;
	return 0;
}

size_t CFileIO::fseek(int offset, int origin)
{
	return std::fseek((FILE*)m_file, offset += m_filesize, origin);
}

size_t CFileIO::ftell()
{
	return 0;
}

size_t CFileIO::fwrite(const char* buf)
{
	size_t length = 0;

	if (buf == NULL)
	{
		return 0;
	}
	else
	{
		length = strlen(buf);
	}

	size_t writeBufResult = fwrite(&length, sizeof(char*));
	size_t writeStrResult = fwrite(buf, length);
	return writeStrResult + writeBufResult;
}

size_t CFileIO::fwrite(const void* buf, size_t count)
{
	return std::fwrite(buf, 1, count, (FILE*)m_file);
}

void CFileIO::fflush()
{

}

CBufferIO::CBufferIO()
{
	m_buffer = NULL;
	m_file = NULL;
	m_bufsize = 0;
	m_filesize = 0;
	CFileIO();
}

CBufferIO::CBufferIO(const CBufferIO& other)
{
	m_filesize = other.m_filesize;
	m_bufsize = other.m_bufsize;
	m_file = other.m_file;
	m_buffer = other.m_buffer;
}

bool CBufferIO::Open(void* buf, size_t size)
{
	m_filesize = size;
	m_bufsize = size;
	m_buffer = buf;
	m_file = (int)m_buffer;
	return true;
}

bool CBufferIO::Open(const char* buf)
{
	bool success = CFileIO::Open(buf);
	bool isOpen = CFileIO::IsOpen();

	if (isOpen)
	{
		LoadBuffer();
	}

	if (!success)
	{
		Close();
	}

	return success;
}

void CBufferIO::Close()
{
	if (m_buffer != NULL)
	{
		free(m_buffer);
	}

	m_file = NULL;
	m_bufsize = 0;
	m_buffer = NULL;
	m_filesize = 0;
	CFileIO::Close();
}

bool CBufferIO::LoadBuffer()
{
	bool success = false;

	if (CFileIO::IsOpen())
	{
		size_t size = GetSize();

		if (0 < size)
		{
			if (m_bufsize < size)
			{
				m_file = (int)realloc((FILE*)m_file, size);
				m_bufsize = size;
			}

			m_filesize = size;

			if (m_file == NULL)
			{
				size = m_filesize;
				int position = CFileIO::fread(m_buffer, size);

				if (size == position)
				{
					m_file = (int)m_buffer;
					success = m_buffer != NULL;
				}
				else
				{
					success = false;
					free((FILE*)m_file);
					m_file = NULL;
					m_bufsize = 0;
					m_filesize = 0;
				}
			}
		}
	}

	return success;
}

void CBufferIO::Release()
{
	m_bufsize = 0;
	m_filesize = 0;
	m_buffer = NULL;
	m_file = NULL;
	CFileIO::Release();
}

size_t CBufferIO::fread(int offset, void** buf)
{
	int position = ftell();
	size_t fileSize = m_filesize;

	if (position < fileSize)
	{
		if (fileSize <= position + offset)
		{
			offset = fileSize - position;
		}

		*buf = (void*)m_file;
		m_file = m_file + offset;
	}
	else
	{
		offset = 0;
	}

	return offset;
}

size_t CBufferIO::fread(void* buf, size_t size)
{
	int position = 0;
	size_t offset = 0;
	size_t fileSize = 0;

	offset = size;
	if (m_buffer == NULL)
	{
		position = CFileIO::fread(buf, offset);
		offset = position;
	}
	else
	{
		position = ftell();
		fileSize = m_filesize;

		if (position < fileSize)
		{
			if (fileSize <= position + size)
			{
				offset = (fileSize - position);
			}

			memcpy(buf, (void*)m_file, offset);
			m_file = m_file + offset;
		}
		else
		{
			offset = 0;
		}
	}

	return offset;
}

size_t CBufferIO::fseek(int offset, int mode)
{
	int pos = 0;

	if (m_file == NULL)
	{
		pos = CFileIO::fseek(offset, mode);
	}
	else
	{
		if (mode == 2)
		{
			pos = m_filesize + offset;
		}
		else if (mode == 1)
		{
			pos = ftell();
			pos += offset;
		}
		else
		{
			pos = 0;
			if (mode == 0)
			{
				pos = offset;
			}
		}

		if (m_filesize < pos || pos < 0)
		{
			pos = -1;
		}
		else
		{
			m_file = (int)m_buffer + pos;
		}
	}

	return pos;
}

size_t CBufferIO::ftell()
{
	int position = 0;

	if (m_buffer == NULL)
	{
		position = CFileIO::ftell();
	}
	else
	{
		position = (int)m_file - (int)m_buffer;
	}

	return position;
}