#include "zrdr.h"

#include <cstring>

#include <freebsd/strcasecmp.h>

#include "zrdr_local.h"
#include "Apps/FTS/gamever.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zUtil/util_systemio.h"
#include "SDL3/SDL_stdinc.h"

bool zrdr_init = false;
bool warnonce = false;

char cur_zrdr_path[256];
s32 cur_zrdr_flags = 0;

ZRDR_TYPE zrdr_file_type = ZRDR_INTEGER;

_zrdr::_zrdr()
{
	type = ZRDR_NULL;
	isclone = false;
	packed = false;
	unused = 0;
	length = 0;

	array = NULL;
}

_zrdr::_zrdr(_zrdr* other, CSTable* stable)
{
	type = ZRDR_NULL;
	isclone = false;
	packed = false;
	unused = 0;
	length = 0;

	Clone(other, stable);
}

bool _zrdr::IsArray() const
{
	return type == ZRDR_ARRAY;
}

void _zrdr::Clone(const _zrdr* other, const CSTable* table)
{
	if (!zrdr_init)
	{
		warnonce = true;
		zrdr_init = true;
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
		return static_cast<s32>(real);
	}

	return 0;
}

_zrdr* _zrdr::Get(s32 offset) const
{
	if (offset < array->length)
	{
		return &array[offset];
	}

	return NULL;
}

u32 _zrdr::GetLength() const
{
	if (type == ZRDR_ARRAY)
	{
		return length;
	}

	return 0;
}

ZRDR_TYPE _zrdr::GetType() const
{
	return (ZRDR_TYPE)type;
}

bool _zrdr::Write(FILE* file)
{
	return _OutputASCII(file, this, 0);
}

_zrdr* zrdr_findtag(_zrdr* reader, const char* name)
{
	return zrdr_findtag_startidx(reader, name, 0);
}

_zrdr* zrdr_findtag_startidx(_zrdr* reader, const char* name, u32 startidx)
{
	if (!reader)
	{
		return NULL;
	}

	if (reader->type != ZRDR_ARRAY)
	{
		return NULL;
	}
	
	for (; startidx < reader->length; startidx++)
	{
		_zrdr* node = &reader->array[startidx];

		if (node->type == ZRDR_ARRAY)
		{
			node = zrdr_findtag_startidx(node, name, 0);

			if (node)
			{
				return node;
			}
		}
		else if (node->type == ZRDR_STRING && strcmp(node->string, name) == 0)
		{
			return &reader->array[startidx + 1];
		}
	}

	return NULL;
}

char* zrdr_findstring(_zrdr* reader, const char* name)
{
	_zrdr* tag = zrdr_findtag(reader, name);
	
	if (!tag)
	{
		return NULL;
	}
	
	if (tag->type == ZRDR_STRING)
	{
		return tag->string;
	}

	if (tag->type == ZRDR_ARRAY && tag->array->type == ZRDR_STRING)
	{
		return tag->array->string;
	}

	return NULL;
}

bool zrdr_findreal(_zrdr* reader, const char* name, f32* output, s32 startidx)
{
	_zrdr* tag = zrdr_findtag(reader, name);

	if (!tag)
	{
		return false;
	}

	if (tag->type != ZRDR_ARRAY)
	{
		return false;
	}

	if (reader->length < startidx + 1)
	{
		return false;
	}

	if (startidx > 0)
	{
		for (u32 i = 0; i < startidx; i++)
		{
			f32 real = 0.0f;
			_zrdr* array = &tag->array[startidx];

			if (array->type == ZRDR_REAL)
			{
				real = array->real;
			}
			else if (array->type == ZRDR_INTEGER)
			{
				real = static_cast<f32>(array->integer);
			}
			else
			{
				real = 0.0f;
			}

			*output = real;
		}
	}
	
	return true;
}

bool zrdr_findint(_zrdr* reader, const char* name, s32* output, s32 startidx)
{
	_zrdr* tag = zrdr_findtag(reader, name);

	if (!tag)
	{
		return false;
	}

	if (tag->type != ZRDR_ARRAY)
	{
		return false;
	}

	if (reader->length < startidx + 1)
	{
		return false;
	}
	
	if (startidx > 0)
	{
		for (u32 i = 0; i < startidx; i++)
		{
			s32 integer = 0;
			_zrdr* array = tag->array;
            
			if (array->type == ZRDR_REAL)
			{
				integer = static_cast<s32>(array->real);
			}
			else if (array->type == ZRDR_INTEGER)
			{
				integer = array->integer;
			}
			else
			{
				integer = output[i];
			}
			
			*output = integer;
		}
	}

	return true;
}

bool zrdr_finduint(_zrdr* reader, const char* name, u32* output, s32 startidx)
{
	_zrdr* tag = zrdr_findtag_startidx(reader, name, startidx);
	return zrdr_toINT(tag, reinterpret_cast<s32*>(output), startidx);
}

bool zrdr_findbool(_zrdr* reader, const char* tag, bool* output)
{
	_zrdr* rdr = zrdr_findtag(reader, tag);
	return zrdr_tobool(rdr, output);
}

bool zrdr_findPNT2D(_zrdr* reader, const char* name, PNT2D* output)
{
	_zrdr* tag = zrdr_findtag_startidx(reader, name, 0);

	if (!tag)
	{
		return false;
	}

	if (tag->type != ZRDR_ARRAY)
	{
		return false;
	}

	if (tag->length < 2)
	{
		return false;
	}

	for (u32 i = 0; i < 2; i++)
	{
		f32 cur_axis = 0.0f;

		_zrdr* array = &tag->array[1];

		if (array[i].type == ZRDR_REAL)
		{
			cur_axis = array[i].real;
		}
		else if (array[i].type == ZRDR_INTEGER)
		{
			cur_axis = static_cast<f32>(array[i].integer);
		}
		else
		{
			cur_axis = (&output->x)[i];
		}

		(&output->x)[i] = cur_axis;
	}
		
	return true;
}

bool zrdr_findPNT3D(_zrdr* reader, const char* name, PNT3D* output)
{
	_zrdr* tag = zrdr_findtag(reader, name);

	if (!tag)
	{
		return false;
	}

	if (tag->type != ZRDR_ARRAY)
	{
		return false;
	}
	
	if (tag->length < 3)
	{
		return false;
	}

	for (u32 i = 0; i < 3; i++)
	{
		f32 cur_axis = 0.0f;

		_zrdr* array = &tag->array[1];

		if (array[i].type == ZRDR_REAL)
		{
			cur_axis = array[i].real;
		}
		else if (array[i].type == ZRDR_INTEGER)
		{
			cur_axis = static_cast<f32>(array[i].integer);
		}
		else
		{
			cur_axis = (&output->x)[i];
		}

		(&output->x)[i] = cur_axis;
	}
		
	return true;
}

bool zrdr_toINT(_zrdr* reader, s32* output, s32 startidx)
{
	if (!reader)
	{
		return false;
	}

	if (reader->type != ZRDR_ARRAY)
	{
		return false;
	}
	
	if (reader->length < startidx + 1)
	{
		return false;
	}

	if (startidx < 0)
	{
		return false;
	}
		
	for (u32 i = 0; i < startidx + 1; i++)
	{
		_zrdr* array = &reader->array[i];
		s32 integer = 0;
        	
		if (array->type == ZRDR_REAL)
		{
			integer = static_cast<s32>(array->real);
		}
		else if (array->type == ZRDR_INTEGER)
		{
			integer = array->integer;
		}
		else
		{
			integer = *output;
		}
				
		*output = integer;
	}

	return true;
}

bool zrdr_toREAL(_zrdr* reader, f32* output, s32 startidx)
{
	if (!reader)
	{
		return false;
	}

	if (reader->type != ZRDR_ARRAY)
	{
		return false;
	}
}

bool zrdr_tobool(_zrdr* reader, bool* output)
{
	if (!output)
	{
		*output = false;
	}

	if (!reader)
	{
		return false;
	}
	
	if (reader->type == ZRDR_ARRAY && reader->length > 1)
	{
		reader = reader->array;
	}

	if (reader->type == ZRDR_INTEGER)
	{
		if (reader->integer == 0)
		{
			*output = false;
			return true;
		}
		
		*output = true;
		return true;
	}
	
	if (reader->type == ZRDR_STRING)
	{
		if (SDL_strcasecmp(reader->string, "true") == 0 || SDL_strcasecmp(reader->string, "on"))
		{
			*output = true;
			return true;
		}
		
		if (SDL_strcasecmp(reader->string, "false") == 0 || SDL_strcasecmp(reader->string, "off"))
		{
			*output = false;
			return true;
		}
	}
	
	return false;
}

_zrdr* _zrdr_nexttag(_zrdr* reader, const char* name, size_t size, _zrdr* other)
{
	s32 i = 8;
	s32 count = 1;

	while (true)
	{
		_zrdr* array = reader->array;

		if (array->integer <= count)
		{
			return NULL;
		}

		if (array == other)
		{
			other = NULL;
		}
		else if (array->type == ZRDR_ARRAY)
		{
			return _zrdr_nexttag(array, name, size, other);
		}
		else if (array->type == ZRDR_STRING && other == NULL && strncmp(array->string, name, size) == 0)
		{
			return array + 1;
		}

		i += 8;
		count++;
	}
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
		s32 it = 0;
		s32 shift = 0;

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

				zfree(array);
				next->real = 0.0f;
			}

			it++;
			shift += 8;
		}

		zfree(array);
		reader->real = 0.0f;
	}
}