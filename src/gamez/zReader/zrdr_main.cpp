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

_zrdr* zrdr_findtag(_zrdr* reader, const char* name)
{

}

_zrdr* zrdr_findtag_startidx(_zrdr* reader, const char* name, int iterations)
{

}

void zrdr_freearray(_zrdr* reader)
{
	if (reader->type == ZRDR_TAG)
	{
		reader->array = NULL;
	}
	else if (reader->type == ZRDR_ARRAY && reader->array != NULL)
	{

	}
}