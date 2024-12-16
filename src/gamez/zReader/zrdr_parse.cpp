#include "zrdr.h"

_zrdr* zrdr_read(const char* name, const char* path, int flags)
{
	if (path == NULL && strlen(path) < 767)
	{
		strcpy(cur_zrdr_path, path);
	}

	cur_zrdr_flags = flags;

	if ((flags & 1) != 0)
	{
		_zrdr* reader = CRdrArchive::FindRdr(name);

		if (reader == NULL)
		{

		}
	}
}