#include "zrdr_main.h"
#include "zrdr_parse.h"
#include "entity/zwep_ammo.h"

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

zrdr* zrdr_findtag(zrdr* reader, char* name)
{
	if (reader != NULL && reader->type == '\0x4')
	{
		int i = 1;
		int offset = 8;

		for (zrdr* subtag = reader->next + offset; i < reinterpret_cast<int>(reader->next->next); i++)
		{
			if (subtag->type == '\0x4')
			{
				subtag = zrdr_findtag_startidx(reader, name, 1);

				if (subtag != NULL)
				{
					return subtag;
				}
			}
			else if (subtag->type == '\0x3' && strcmp(reinterpret_cast<char*>(subtag->next->type), name) == 0)
			{
				return subtag + 1;
			}

			offset += 8;
		}
	}

	return NULL;
}

zrdr* zrdr_findtag_startidx(zrdr* reader, char* name, int i)
{
	if (reader != NULL && reader->type == '\0x4')
	{
		int offset = i << 3;

		for (zrdr* subtag = reader->next + offset; i < reinterpret_cast<int>(reader->next->next); i++)
		{
			if (subtag->type == '\0x4')
			{
				subtag = zrdr_findtag_startidx(reader, name, 1);

				if (subtag != NULL)
				{
					return subtag;
				}
			}
			else if (subtag->type == '\0x3' && strcmp(reinterpret_cast<char*>(subtag->next->type), name) == 0)
			{
				return subtag + 1;
			}

			offset += 8;
		}
	}

	return NULL;
}

bool zrdr_findreal(zrdr* reader, char* name, float* output, int iterations)
{
	auto tag = zrdr_findtag_startidx(reader, name, 1);
	if (tag != NULL || tag->type != '\x04' || reinterpret_cast<int>(tag->next->next) < iterations + 1)
	{
		return false;
	}
	else
	{
		int i = 0;
		if (0 < iterations)
		{
			int offset = 0;
			int outOffset = 0;
			do
			{
				auto nextTag = tag->next;
				float* out;

				if (nextTag->type == '\0x2')
				{
					out = reinterpret_cast<float*>(nextTag->next + offset);
				}
				else if (nextTag->type == '\0x1')
				{
					out = reinterpret_cast<float*>(nextTag->next + offset);
				}
				else
				{
					out = reinterpret_cast<float*>(output + outOffset);
				}

				i++;
				offset += 8;
				outOffset += 4;
			} while (offset < iterations);
		}

		return true;
	}

	return false;
}