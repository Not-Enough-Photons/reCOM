#include "zrdr.h"
#include "Apps/FTS/gamever.h"

#include "gamez/zSystem/zsys.h"
#include "gamez/zUtil/util_stack.h"
#include "SDL3/SDL_log.h"

char* buffer = NULL;

s32 CRdrArchive::version = 1;

CRdrFile::CRdrFile()
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

		// TODO: Implement a proper way to delete the string table
		// delete &file->m_strings;

		// TODO: Implement destructor for CRdrFile
		// delete file;
	}

	return 0;
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

			// Tag end
			if (symbol == ')')
			{
				if ((!endline) && (!comment))
				{
					i--;
				}
			}
			else
			{
				// Tag begin
				if (symbol == '(')
				{
					if (!endline && !comment)
					{
						i++;
					}
				}
				else
				{
					// New-line or carriage return
					if ((symbol == '\n') || (symbol == '\r'))
					{
						if (!endline)
						{
							comment = false;
						}
					}
					else
					{
						// Comment
						if (symbol == ';')
						{
							if (!endline)
							{
								comment = true;
							}
						}
						else
						{
							// Include path
							if ((symbol == '\"') && (!comment))
							{
								endline = (bool)(endline ^ 1);
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

CRdrFile* CRdrFile::Load(zar::CZAR* archive, zar::CKey* key, u32 flags)
{
	bool got_list = false;
	CRdrFile* file = NULL;

	if (key)
	{
		if (key->GetSize() != -1)
		{
			CRdrFile* buf = NULL;

			if ((flags & ZRDR_FLAG_ALLOC) == 0)
			{
				buf = static_cast<CRdrFile*>(zcalloc(key->GetSize(), 1));
				got_list = archive->Fetch(key, buf, key->GetSize());
			}
			else
			{
				got_list = archive->FetchLIP(key, reinterpret_cast<void**>(&buf));
			}

			if (got_list)
			{
				file = Read(buf, key->GetSize(), flags);
			}
		}
	}

	return file;
}

CRdrFile* CRdrFile::Read(_zrdr* reader, size_t size, u32 flags)
{
	CRdrFile* file = NULL;

	if (reader->type == zrdr_file_type)
	{
		file = new CRdrFile();
	}

	file->m_buffer = reinterpret_cast<char*>(reader);
	file->type = ZRDR_ARRAY;
	file->array = NULL;

	if (!file->Resolve(false))
	{
		// TODO: cleanup after resolution failure
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "zReader file failed to read!");
		file = NULL;
	}
	
	return file;
}

bool CRdrFile::Resolve(bool resolveA)
{
	struct zrdr_file_header
	{
		_zrdr reader;
		u32 offset;
	} *header_t;
	
	header_t = reinterpret_cast<zrdr_file_header*>(m_buffer);
	_zrdr* resolved = NULL;
	char* start = NULL;
	char* str = NULL;
	char* table = NULL;

	if (!header_t)
	{
		return false;
	}

	str = NULL;
	resolved = NULL;

	if (header_t)
	{
		str = reinterpret_cast<char*>(header_t + 1);
		resolved = reinterpret_cast<_zrdr*>(m_buffer + header_t->offset);
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
				table = start + sizeof(zrdr_file_header);
			}

			m_strings.LoadTable(table, reinterpret_cast<u32>(start), false);
			return true;
		}

		_resolveB(resolved, resolved, str);
	}

	start = m_buffer;

	table = NULL;

	if (start)
	{
		table = start + sizeof(zrdr_file_header);
	}

	m_strings.LoadTable(table, header_t->reader.integer, false);
	this->array = resolved;
	this->length = 1;
	return true;
}