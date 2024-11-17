#include <cstring>

#include "bsd/strcasecmp.h"

#include "zrdr_main.h"

#include "gamez/zUtil/util_main.h"
#include "gamez/zUtil/util_systemio.h"
#include "gamez/zWeapon/zwep_weapon.h"

bool init = false;
bool warnonce = false;

_zrdr::_zrdr(const _zrdr* other, const CSTable* table)
{
	Clone(other, table);
}

bool _zrdr::IsArray() const
{
	return type == ZRDR_ARRAY;
}

void _zrdr::Clone(const _zrdr* other, const CSTable* table)
{
	if (!init)
	{
		warnonce = true;
		init = true;
	}

	if (other == NULL)
	{
		return;
	}

	
	type = other->type;
	if (type == ZRDR_ARRAY)
	{

	}
}

int _zrdr::GetInt() const
{
	if (type == ZRDR_INTEGER)
	{
		return integer;
	}
	else if (type == ZRDR_REAL)
	{
		return static_cast<int>(real);
	}

	return 0;
}

char* _zrdr::Get(int offset) const
{
	int length = 0;

	if (type == ZRDR_ARRAY)
	{
		length = array->integer - 1;
	}

	if (offset < length)
	{
		return string + (offset + 1) * 8;
	}

	return NULL;
}

_zrdr* zrdr_findtag(_zrdr* reader, const char* name)
{
	if (reader != NULL && reader->type == ZRDR_ARRAY)
	{
		int iterations = 0;
		for (int max_depth = 8; iterations < reader->array->integer; iterations++)
		{
			auto rdr = reader->array;

			if (rdr->type == ZRDR_ARRAY)
			{
				rdr = zrdr_findtag_startidx(rdr, name, 1);

				if (rdr != NULL)
				{
					return rdr;
				}
			}
			else if (rdr->type == ZRDR_STRING && strcmp(rdr->string, name) == 0)
			{
				return rdr + 1;
			}

			max_depth += 8;
		}
	}

	return NULL;
}

_zrdr* zrdr_findtag_startidx(_zrdr* reader, const char* name, int iterations)
{
	if (reader != NULL && reader->type == ZRDR_ARRAY)
	{
		for (int max_depth = iterations << 3; iterations < reader->array->integer; iterations++)
		{
			auto rdr = reader->array;

			if (rdr->type == ZRDR_ARRAY)
			{
				rdr = zrdr_findtag_startidx(rdr, name, 1);

				if (rdr != NULL)
				{
					return rdr;
				}
			}
			else if (rdr->type == ZRDR_STRING && strcmp(rdr->string, name) == 0)
			{
				return rdr + 1;
			}

			max_depth += 8;
		}
	}

	return NULL;
}

void zrdr_freearray(_zrdr* reader)
{
	_zrdr* array = NULL;

	if (reader->type == ZRDR_REAL)
	{
		reader->real = 0.0f;
	}
	else if (reader->type == ZRDR_ARRAY && reader->integer != 0)
	{
		int it = 0;
		int shift = 0;

		while (true)
		{
			array = reader->array;
			auto next = array + shift;

			if (next->integer <= it)
			{
				break;
			}

			if (next->type == ZRDR_REAL)
			{
				next->real = 0.0f;
			}
			else if (next->type == ZRDR_ARRAY && next->integer != 0)
			{
				int subshift = 0;

				for (int subit = 0; subit < next->array->integer; subit++)
				{
					zrdr_freearray(array + subshift);
					subshift += 8;
				}

				free(array);
				next->real = 0.0f;
			}

			it++;
			shift += 8;
		}

		free(array);
		reader->real = 0.0f;
	}
}