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
		sprintf(buffer, "%s/%s", name, dir);
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
	_zrdr* buffer = reinterpret_cast<_zrdr*>(m_buffer);
	_zrdr* array = NULL;
	_zrdr* other = NULL;
	_zrdr* resolved_rdr = NULL;

	if (!buffer)
	{
		return false;
	}

	array = NULL;
	
	if (resolveA)
	{
		array = NULL;

		if (buffer)
		{
			array = buffer + 1;
		}

		other = NULL;

		if (buffer)
		{
			other = buffer->array;
		}

		if (type != ZRDR_STRING)
		{
			s32 i = 1;
			if (type == ZRDR_ARRAY)
			{
				_zrdr* child = NULL;
				s32 rdridx = 0;
				while (true)
				{
					child = this->array;

					if (child->integer <= i)
					{
						break;
					}

					_resolveA(child->array, other, child->string);
					rdridx += 8;
					i++;
				}
			}
		}
	}

	resolved_rdr = NULL;

	if (buffer)
	{	
		array = buffer + 1;
		// Go to the very first zrdr entry below the string table.
		// This is calculated by taking the address of the array
		// and adding its length in bytes to get there.
		resolved_rdr = (_zrdr*)((char*)buffer + array->length);
	}

	if (type == ZRDR_STRING)
	{
		this->string = this->string + (s32)array;
	}
	else
	{
		if (type != ZRDR_ARRAY)
		{
			array = NULL;
			
			if (buffer)
			{
				array = buffer + 1;
			}

			this->array = resolved_rdr;

			u32 next = sizeof(_zrdr);
			for (u32 i = 1; i < array->length; i++)
			{
				_resolveB(this->array + next, resolved_rdr, (char*)(array + 1));
				next += sizeof(_zrdr);
			}
			
			m_strings.LoadTable(array + 1, buffer->length, false);
			return true;
		}
	}
	
	return true;
}