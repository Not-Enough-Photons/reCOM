#include "zrdr.h"

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
			free(file->m_buffer);
			file->m_buffer = NULL;
			file->m_size = 0;
		}

		file->m_strings.~CSTable();
		delete file;
	}
}