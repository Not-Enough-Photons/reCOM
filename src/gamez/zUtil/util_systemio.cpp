#include "util_systemio.h"

char* CFileIO::PS2FileName(char* file, char* directory, int param_3)
{
	char nameBuf[512];
	char tokenBuf[512];
	char* token;
	int length = 0;

	strcpy(nameBuf, file);
	strcpy(tokenBuf, '\0');
	token = strtok(nameBuf, "/\\");

	if (token != 0)
	{
		while (true)
		{
			strcat(tokenBuf, token);
			token = strtok(0, "/\\");
			if (token == 0)
			{
				break;
			}

			strcat(tokenBuf, "\\\0");
		}
	}

	if (param_3 == 0 /*|| CFileCD::m_TOC == 0*/)
	{
		sprintf(directory, "%s%s", "host0:.\\", tokenBuf);
		length = strlen(m_root_path);
	}
	else
	{
		strcpy(directory, tokenBuf);
		length = 0;
	}

	int directoryLength = strlen(directory);

	for (; length < directoryLength; length++)
	{
		int c = toupper(directory[length]);
		directory[length] = c;
	}

	token = (char*)strstr(m_root_path, "cdrom");

	if (token != 0)
	{
		token = strcat(directory, ";1");
	}

	return token;
}

bool CFileIO::Open(char* file, OpenFlags flags)
{
	char directory[1024];
	CFileIO::PS2FileName(file, directory, 1);

	if (m_write_status == 0)
	{
		OpenFlags flag = (OpenFlags)(flags & 1 != 0);

		if ((flags & OpenFlags::WRITE) != 0)
		{
			flag = (OpenFlags)(flag | OpenFlags::WRITE);
		}

		if ((flags & OpenFlags::APPEND) != 0)
		{
			flag = (OpenFlags)(flag | OpenFlags::APPEND);
		}

		if ((flags & 8) != 0)
		{
			flag = (OpenFlags)(flag | OpenFlags::CREATE);
		}

		FILE* file = std::fopen(directory, 0);
		m_file = file;

		if (m_write_status == 0)
		{
			if (m_file && (flags & OpenFlags::READ) != 0)
			{
				m_filesize = std::fseek(m_file, 0, 2);
				std::fseek(m_file, 0, 0);
			}
		}
		else
		{
			strstr(directory, ":");
			m_filesize = 0;
		}
	}
	else
	{
		// TODO:
		// Finish the rest of this function
	}

	return true;
}

int CFileIO::fwrite(const void* buf, int count)
{
	return std::fwrite(buf, 4, count, m_file);
}

int CBufferIO::fwrite(const void* buf, int count)
{
	if (is_open == 0)
	{
		return CFileIO::fwrite(buf, count);
	}

	return -1;
}