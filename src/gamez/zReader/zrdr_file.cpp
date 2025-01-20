#include "zrdr.h"

#include "gamez/zSystem/zsys.h"
#include "gamez/zUtil/util_stack.h"

char* buffer = NULL;

CRdrFile::CRdrFile() : _zrdr()
{
	m_buffer = NULL;
	m_size = 0;
}

const char* zrdr_findfile(const char* name, const char* dir)
{
	if (dir)
	{
		sprintf_s(buffer, 64, "%s/%s", name, dir);
		name = buffer;
	}

	return name;
}

int zrdr_free(CRdrFile* file)
{
	if (file != NULL)
	{
		if (file->m_buffer == NULL)
		{
			zrdr_freearray(file);
		}
		else
		{
			zfree(file->m_buffer);
			file->m_buffer = NULL;
			file->m_size = 0;
		}

		file->m_strings.~CSTable();

		// TODO: Implement destructor for CRdrFile
		// delete file;
	}

	return 0;
}

CRdrFile* CRdrFile::ReadArray()
{
	return NULL;
}

bool CRdrFile::ValidateFormat()
{
	CBufferIO* file = NULL;
	char symbol = '\0';
	bool validated = false;
	bool endline = false;
	bool comment = false;
	s32 i = 0;
	
	do
	{
		while (true)
		{
			file = fstack.front();

			if (!file->fread(&symbol, 1))
			{
				break;
			}

			validated = true;
			
			if (!validated)
			{
				file->fseek(0, SEEK_SET);
				return i == 0;
			}

			if (symbol == ')')
			{
				if (!endline && !comment)
				{
					i--;
				}
			}
			else
			{
				if (symbol == '(')
				{
					if (!endline && !comment)
					{
						i++;
					}
				}
				else
				{
					if (symbol == '\n' || symbol == '\r')
					{
						if (!endline)
						{
							comment = false;
						}
					}
					else
					{
						if (symbol == ';')
						{
							if (!endline)
							{
								comment = true;
							}
						}
						else
						{
							if (symbol == '\"' && !comment)
							{
								endline = true;
							}
						}
					}
				}
			}
		}

		if (fstack.size() < 2)
		{
			validated = false;
			file->fseek(0, SEEK_SET);
			return i == 0;
		}

		fstack.pop(true);
	} while (true);
}

CRdrFile* CRdrFile::Load(zar::CZAR* archive, zar::CKey* key)
{
	CRdrFile* rdrFile = new CRdrFile();

	if (key != NULL)
	{
		size_t keySize = key->GetSize();

		if (keySize != -1)
		{
			void* zrdr_buf = zmalloc(keySize);

			if (archive->Fetch(key, zrdr_buf, keySize))
			{
				CSTable stable = CSTable(0, 1024);
				rdrFile->m_strings = stable;
				rdrFile->m_buffer = static_cast<char*>(zrdr_buf);
				rdrFile->m_size = keySize;
				rdrFile->type = ZRDR_ARRAY;
				rdrFile->array = NULL;
				rdrFile->Resolve(false);
			}
		}
	}

	return rdrFile;
}

bool CRdrFile::Resolve(bool resolveA)
{
	_zrdr* header = reinterpret_cast<_zrdr*>(m_buffer);
	_zrdr* resolved = NULL;
	char* str = NULL;
	char* start = NULL;
	char* table = NULL;

	if (!header)
	{
		return false;
	}

	str = NULL;

	if (resolveA)
	{
		
	}

	resolved = NULL;

	if (header)
	{
		str = reinterpret_cast<char*>(header + 1);
		resolved = reinterpret_cast<_zrdr*>(m_buffer + header->integer);
	}

	if (type == ZRDR_STRING)
	{
		this->string = str;
	}
	else
	{
		if (type != ZRDR_ARRAY)
		{
			start = m_buffer;
			table = NULL;

			if (start)
			{
				table = start + sizeof(_zrdr);
			}

			m_strings.LoadTable(table, reinterpret_cast<u32>(start), false);
			return true;
		}

		this->array = resolved;
		
		for (u32 i = 1; this->array->integer; i++)
		{
			_resolveB(&this->array[i], resolved, str);
		}
	}

	start = m_buffer;

	table = NULL;

	if (start)
	{
		table = start + sizeof(_zrdr);
	}

	m_strings.LoadTable(table, reinterpret_cast<u32>(start), false);
	return true;
}