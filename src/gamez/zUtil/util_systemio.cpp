#include <sys/stat.h>

#include "util_systemio.h"

#include "gamez/zSystem/zsys_main.h"



char* CFileIO::PS2FileName(const char* file, char* directory, int param_3)
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

	if (param_3 == 0 && CFileCD::m_TOC != 0)
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

bool CFileIO::Open(const char* file, unsigned int mode)
{
	char directory[1024];
	CFileIO::PS2FileName(file, directory, 1);

	m_mode = mode;

	// Is the file system not on the CD?
	if (!zSys.isCdBoot)
	{
		unsigned int modeFlags = (mode & 1) != 0;

		if ((mode & S_IWOTH) != 0)
		{
			modeFlags |= S_IWOTH;
		}

		if ((mode & S_IXGRP) != 0)
		{
			modeFlags |= S_IRUSR;
		}

		if ((mode & S_IRWXO) != 0)
		{
			modeFlags |= S_IWUSR;
		}

		FILE* fd = std::fopen(directory, "r");
		m_file = (int)fd;

		if (!zSys.isCdBoot)
		{
			if (m_file != NULL && (mode & S_IXOTH) != 0)
			{
				size_t filesize = std::fseek((FILE*)m_file, 0, SEEK_END);
				m_filesize = filesize;
				std::fseek((FILE*)m_file, 0, SEEK_SET);
			}
		}
		else
		{
			strstr(directory, ":");
			m_filesize = 0; // unaff_s0_lo - i don't know why the hell it was there
		}
	}
	// File system is on the CD
	// Read contents from game disc
	else
	{
		CFileCD* cd = new CFileCD();
		if (cd != NULL)
		{
			cd->m_headSector = -1;
			cd->m_toc = NULL;
			cd->m_pos = 0;
			cd->m_buf = NULL;
			cd->m_sector = static_cast<char*>(memalign(64, 2048));
		}

		m_cd = cd;

		_FILECD* dir_fd = CFileCD::Find(directory);
		cd->m_toc = dir_fd;

		// File table of contents exists for our CD?
		if (cd->m_toc != NULL)
		{
			// Go to the beginning
			cd->m_pos = 0;
			unsigned int startSector = cd->m_toc->startSector;

			// Make the head sector go to the very beginning
			if (cd->m_headSector != startSector)
			{
				cd->m_headSector = startSector;
				cd->m_buf = NULL;
			}
		}

		// If for whatever reason the table of contents gets unloaded
		if (cd->m_toc == NULL)
		{
			// If the CD file still exists
			if (m_cd != NULL)
			{
				// Get its current sectors
				if (m_cd->m_sector != NULL)
				{
					free(m_cd->m_sector);
				}

				// Dispose of them
				m_cd->m_sector = NULL;
				delete(m_cd);
			}

			m_file = 0;
		}
		else
		{
			m_filesize = m_cd->m_pos;
		}
	}

	bool open = false;

	if (!zSys.isCdBoot)
	{
		open = -1 < m_file;
	}
	else
	{
		open = m_file != -1;
		
		if (open)
		{
			open = m_file != 0;
		}
	}

	return open;
}

void CFileIO::Close()
{
	bool open = false;

	if (zSys.isCdBoot)
	{
		open = m_file != -1;

		if (open)
		{
			open = m_file != 0;
		}
	}
	else
	{
		open = -1 < m_file;
	}

	if (open)
	{
		if (zSys.isCdBoot && m_cd != NULL)
		{
			if (m_cd->m_sector != NULL)
			{
				free(m_cd->m_sector);
			}

			m_cd->m_sector = NULL;
			delete(m_cd);
		}
		else
		{
			std::fclose((FILE*)m_file);
		}

		m_file = -1;
	}
}

size_t CFileIO::fread(void* buf, size_t size)
{
	if (size == 0)
	{
		return 0;
	}
	else if (zSys.isCdBoot)
	{
		return m_cd->Read(buf, size);
	}
	else
	{
		return std::fread(buf, size, size, (FILE*)m_file);
	}

	return 0;
}

size_t CFileIO::fread(int offset, void** buf)
{
	*buf = NULL;
	return 0;
}

size_t CFileIO::fwrite(const void* buf, size_t count)
{
	if (!zSys.isCdBoot)
	{
		return std::fwrite(buf, count, count, (FILE*)m_file);
	}

	return 0;
}

void CBufferIO::Close()
{
	if (m_cd != NULL)
	{
		free(m_cd);
	}

	m_cd = NULL;
	m_filesize = 0;
	m_file = 0;
	m_mode = OpenFlags::NONE;
	CFileIO::Close();
}