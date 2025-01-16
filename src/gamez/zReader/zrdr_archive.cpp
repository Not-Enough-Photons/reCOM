#include "freebsd/strcasecmp.h"

#include "zrdr.h"

#include "gamez/zUtil/zutil.h"
#include "gamez/zUtil/util_stable.h"
#include "gamez/zUtil/util_systemio.h"

std::list<zar::CZAR*> CRdrArchive::m_list;

zar::CZAR* CRdrArchive::AddArchive(const char* name, const char* path)
{
	char archiveName[1024];
	zar::CZAR* output = NULL;

	if (path == NULL)
	{
		strcpy(archiveName, name);
	}
	else
	{
		sprintf(archiveName, "%s/%s", path, name);
	}

	for (auto it = m_list.begin(); it != m_list.end(); it++)
	{
		zar::CZAR* archive = *it;

		if (strcasecmp(archive->m_filename, archiveName) == 0)
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

		if (strstr(archive->m_filename, fullPath) != 0)
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

	return false;
}

CRdrFile* CRdrArchive::FindRdr(const char* reader)
{
	CRdrFile* rdr = NULL;
	char keyName[1024];
	const char* subpath = strrchr(reader, '/');

	if (subpath == NULL)
	{
		if (keyName != NULL)
		{
			strcpy(keyName, reader);
		}
	}
	else if (subpath[1] != '\0')
	{
		if (keyName != NULL)
		{
			strcpy(keyName, subpath + 1);
		}
	}

	for (auto it = m_list.begin(); it != m_list.end(); ++it)
	{
		if (rdr)
		{
			return rdr;
		}

		bool open = false;

		zar::CZAR* archive = *it;

		if (!archive->m_pFileAlloc)
		{
			open = false;
		}
		else
		{
			open = archive->m_pFileAlloc->IsOpen();
		}

		if (!open)
		{
			archive->ReOpen(1, OpenFlags::READ);
		}

		rdr = NULL;
		zar::CKey* key = archive->OpenKey(keyName);
		if (key)
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
		std::cout << archive << std::endl;
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