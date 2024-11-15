#include "bsd/strcasecmp.h"

#include "zrdr_main.h"

#include "gamez/zUtil/util_main.h"
#include "gamez/zUtil/util_systemio.h"

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