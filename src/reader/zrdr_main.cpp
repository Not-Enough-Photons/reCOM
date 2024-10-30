#include "zrdr_main.h"
#include "zrdr_parse.h"
#include "entity/zwep_ammo.h"

bool init = false;
bool warnonce = false;

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

		FILE* file = std::fopen(directory, GetMode(flag));
		this->file = file;

		if (m_write_status == 0)
		{
			if (this->file && (flags & OpenFlags::READ) != 0)
			{
				position = std::fseek(this->file, 0, 2);
				std::fseek(this->file, 0, 0);
			}
		}
		else
		{
			strstr(directory, ":");
			position = 0;
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
	return std::fwrite(buf, 4, count, file);
}

int CBufferIO::fwrite(const void* buf, int count)
{
	if (is_open == 0)
	{
		return CFileIO::fwrite(buf, count);
	}

	return -1;
}

_zrdr::_zrdr(const _zrdr* other, const CSTable* table)
{
	Clone(other, table);
}

void _zrdr::Clone(const _zrdr* other, const CSTable* table)
{
	if (!init)
	{
		warnonce = true;
		init = true;
	}

	if (other == NULL)
	{
		return;
	}

	type = other->type;
	if (type == TYPE_ARRAY)
	{

	}
}

_zrdr* zrdr_findtag(const char* name)
{

}

_zrdr* zrdr_findtag_startidx(const char* name, int iterations)
{

}