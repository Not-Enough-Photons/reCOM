#include <cstring>

#include "lib-bsd/strcasecmp.h"

#include "zrdr_main.h"
#include "zrdr_parse.h"

#include "gamez/zWeapon/zwep_weapon.h"
#include "gamez/zUtil/util_main.h"

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

		FILE* file = std::fopen(directory, 0);
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
	if (type == ZRDR_ARRAY)
	{

	}
}

_zrdr* zrdr_findtag(_zrdr* reader, const char* name)
{

}

_zrdr* zrdr_findtag_startidx(_zrdr* reader, const char* name, int iterations)
{

}

void zrdr_freearray(_zrdr* reader)
{
	int mem_line = 0;
	int rdr_count = 0;

	if (reader->type == ZRDR_TAG)
	{
		reader->value = 0;
	}
	else if (reader->type == ZRDR_ARRAY && reader->value != 0)
	{
		mem_line = 0;

		_zrdr* arr = cast_rdr_array(reader->value);
		_zrdr* cur = cast_rdr_array(arr + mem_line);

		// TODO:
		// Finish the rest of this function
	}
}

zar::CZAR* CRdrArchive::AddArchive(const char* name, const char* path)
{
	char* archiveName = 0;
	zar::CZAR* output;

	if (!string_exists(path))
	{
		strcpy(archiveName, path);
	}
	else
	{
		sprintf(archiveName, "%s/%s");
	}

	for (auto it = m_list.begin(); it != m_list.end(); it++)
	{
		zar::CZAR* archive = *it;
			
		if (strcasecmp(archive->name, archiveName) == 0)
		{
			output = archive;
			break;
		}
	}

	if (output == NULL)
	{
		output = new zar::CZAR(archiveName, NULL);
		m_list.insert(m_list.begin(), output);
	}

	return output;
}

bool CRdrArchive::RemoveArchive(const char* name, const char* path)
{
	char* fullPath;
	sprintf(fullPath, "%s/s", path, name);

	for (auto it = m_list.begin(); it != m_list.end(); it++)
	{
		zar::CZAR* archive = *it;

		if (!string_exists(strstr(archive->name, fullPath)))
		{
			continue;
		}
		else
		{
			m_list.erase(it);
			archive->Close();

			if (archive != NULL)
			{
				archive->~CZAR();
			}
		}
	}
}

CRdrFile* CRdrArchive::FindRdr(const char* reader)
{
	CRdrFile* rdr;
	char* readerName;
	const char* lastSlash = strrchr(reader, '/');

	if (!string_exists(lastSlash) && string_exists(reader))
	{
		strcpy(readerName, reader);
	}
	else if (lastSlash[1] != 0 && string_exists(reader))
	{
		strcpy(readerName, lastSlash + 1);
	}

	for (auto it = m_list.begin(); it != m_list.end() && lastSlash != NULL; it++)
	{
		if (rdr != NULL)
		{
			return rdr;
		}

		bool open = false;

		zar::CZAR* archive = *it;

		if (archive->bufferIO == NULL)
		{
			open = false;
		}
		else
		{
			open = archive->bufferIO->IsOpen();
		}

		if (!open)
		{
			archive->ReOpen(1, OpenFlags::READ);
		}

		rdr = NULL;
		zar::CKey* key = archive->OpenKey(readerName);
		if (key != NULL)
		{
			rdr = CRdrFile::Load(archive, key);
			archive->CloseKey(key);
		}

		if (!open)
		{
			archive->Close();
		}
	}

	return rdr;
}

void CRdrArchive::OpenAll()
{
	for (auto it = m_list.begin(); it != m_list.end(); it++)
	{
		zar::CZAR* archive = *it;
		archive->ReOpen(1, OpenFlags::READ);
	}
}

void CRdrArchive::CloseAll()
{
	for (auto it = m_list.begin(); it != m_list.end(); it++)
	{
		zar::CZAR* archive = *it;
		archive->Close();
	}
}