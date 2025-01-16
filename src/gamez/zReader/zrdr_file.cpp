#include "zrdr.h"

#include "gamez/zSystem/zsys.h"

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
				Resolve(rdrFile, false);
			}
		}
	}

	return rdrFile;
}

bool CRdrFile::Resolve(CRdrFile* file, bool resolveA)
{
	_zrdr* buffer = reinterpret_cast<_zrdr*>(file->m_buffer);
	_zrdr* array = NULL;

	if (!buffer)
	{
		return false;
	}

	if (resolveA)
	{
		if (buffer)
		{
			
		}
	}

	return true;
}