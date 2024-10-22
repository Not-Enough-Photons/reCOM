#include "zrdr_main.h"
#include "zrdr_parse.h"

#include "entity/zwep_ammo.h"

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

void* CRdrIO::zrdr_findbool(CZAREntry* entry, const char* param_2, int param_3)
{
	auto tag = zrdr_findtag_startidx(entry, param_2, 1);
}

void CFileIO::Release()
{
	field4_0x4 = 0xffffffff;
}

void CBufferIO::Release()
{
	field14_0x14 = 0;
	field15_0x18 = 0;
	field16_0x1c = 0;
	field13_0x10 = 0;
	CFileIO::Release();
}