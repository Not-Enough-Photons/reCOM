#include "zrdr.h"

#include <cstring>

#include <freebsd/strcasecmp.h>

#include "zrdr_local.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zUtil/util_systemio.h"

bool zrdr_init = false;
bool warnonce = false;

char cur_zrdr_path[256];
s32 cur_zrdr_flags = 0;

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

char* _zrdr::Get(s32 offset) const
{
	s32 length = 0;

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

bool _zrdr::Write(FILE* file)
{
	return _OutputASCII(file, this, 0);
}

_zrdr* zrdr_findtag(_zrdr* reader, const char* name)
{
	return zrdr_findtag_startidx(reader, name, 1);
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
	
	for (; startidx < reader->array->integer; startidx++)
	{
		_zrdr* node = &reader->array[startidx];

		if (node->type == ZRDR_ARRAY)
		{
			node = zrdr_findtag_startidx(node, name, 1);

			if (node)
			{
				return node;
			}
		}
		else if (node->type == ZRDR_STRING && strcmp(node->string, name) == 0)
		{
			return &node[1];
		}
	}

	return NULL;
}

char* zrdr_findstring(_zrdr* reader, const char* name)
{
	char* str = NULL;
	auto tag = zrdr_findtag_startidx(reader, name, 1);

	if (!tag)
	{
		str = NULL;
	}
	else if (tag->type == ZRDR_STRING)
	{
		str = tag->string;
	}
	else if (tag->type == ZRDR_ARRAY && tag->array[1].type == ZRDR_STRING)
	{
		str = tag->array[1].string;
	}
	else
	{
		str = NULL;
	}

	return str;
}

bool zrdr_findreal(_zrdr* reader, const char* name, f32* output, s32 iterations)
{
	u32 i = 0;
	bool found = false;
	_zrdr* tag = zrdr_findtag_startidx(reader, name, 1);

	if (!tag || tag->type != ZRDR_ARRAY || tag->array->integer < iterations + 1)
	{
		found = false;
	}
	else
	{
		i = 0;

		if (iterations > 0)
		{
			do
			{
				f32 real = 0.0f;
				_zrdr* array = tag->array;

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
				
				i++;
				*output = real;
			} while (i < iterations);
		}

		found = true;
	}
	
	return found;
}

bool zrdr_findint(_zrdr* reader, const char* name, s32* output, s32 iterations)
{
	u32 i = 0;
	bool found = false;
	_zrdr* tag = zrdr_findtag_startidx(reader, name, 1);

	if (!tag || tag->type != ZRDR_ARRAY || tag->array->integer < iterations + 1)
	{
		found = false;
	}
	else
	{
		i = 0;

		if (iterations > 0)
		{
			do
			{
				s32 integer = 0;
				_zrdr* array = tag->array;

				if (array[1].type == ZRDR_REAL)
				{
					integer = static_cast<s32>(array[1].real);
				}
				else if (array[1].type == ZRDR_INTEGER)
				{
					integer = array[1].integer;
				}
				else
				{
					integer = output[i];
				}
				
				i++;
				*output = integer;
			} while (i < iterations);
		}

		found = true;
	}
	
	return found;
}

bool zrdr_finduint(_zrdr* reader, const char* name, u32* output, s32 iterations)
{
	_zrdr* tag = zrdr_findtag_startidx(reader, name, iterations);
	return zrdr_toINT(tag, reinterpret_cast<s32*>(output), iterations);
}

bool zrdr_findbool(_zrdr* reader, const char* tag, bool* output)
{
	_zrdr* rdr = zrdr_findtag_startidx(reader, tag, 1);
	return zrdr_tobool(rdr, output);
}

bool zrdr_findPNT2D(_zrdr* reader, const char* name, PNT2D* output)
{
	u32 i = 0;
	bool found = false;
	_zrdr* tag = zrdr_findtag_startidx(reader, name, 1);

	if (!tag || tag->type != ZRDR_ARRAY || tag->array->integer < 3)
	{
		found = false;
	}
	else
	{
		i = 0;

		f32 axis = 0.0f;

		do
		{
			_zrdr* array = tag->array;

			if (array[i].type == ZRDR_REAL)
			{
				axis = array[i].real;
			}
			else if (array[i].type == ZRDR_INTEGER)
			{
				axis = static_cast<f32>(array[i].integer);
			}
			else
			{
				axis = *(f32*)(output + i);
			}

			*(f32*)(output + i) = axis;
				
			i++;
		} while (i < 2);

		found = true;
	}
	
	return found;
}

bool zrdr_findPNT3D(_zrdr* reader, const char* name, PNT3D* output)
{
	u32 i = 0;
	bool found = false;
	_zrdr* tag = zrdr_findtag_startidx(reader, name, 1);

	if (!tag || tag->type != ZRDR_ARRAY || tag->array->integer < 3)
	{
		found = false;
	}
	else
	{
		i = 1;

		f32 axis = 0.0f;

		do
		{
			_zrdr* array = tag->array;

			if (array[1].array[i].type == ZRDR_REAL)
			{
				axis = array[1].array[i].real;
			}
			else if (array[1].array[i].type == ZRDR_INTEGER)
			{
				axis = static_cast<f32>(array[1].array[i].integer);
			}
			else
			{
				axis = *(f32*)(output + i);
			}

			*(f32*)(output + i) = axis;
				
			i++;
		} while (i < 3);

		found = true;
	}
	
	return found;
}

bool zrdr_toINT(_zrdr* reader, s32* output, s32 size)
{
	bool success = false;
	u32 i = 0;
	
	if (!reader || reader->type != ZRDR_ARRAY || reader->array->integer < size + 1)
	{
		success = false;
	}
	else
	{
		if (size > 0)
		{
			i = 0;

			do
			{
				_zrdr* array = reader->array;
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
				
				i++;
				*output = integer;
			} while (i < size);
		}

		success = true;
	}

	return success;
}

bool zrdr_toREAL(_zrdr* reader, f32* output, s32 size)
{
	u32 i = 0;
	bool success = false;
	
	if (!reader || reader->type != ZRDR_ARRAY || reader->array->integer < size + 1)
	{
		success = false;
	}
	else
	{
		if (size > 0)
		{
			i = 0;
			do
			{
				_zrdr* array = reader->array;
				f32 real = 0.0f;
				
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
					real = *output;
				}

				i++;
				*output = real;
			}
			while (i < size);
		}

		success = true;
	}

	return success;
}

bool zrdr_tobool(_zrdr* reader, bool* output)
{
	bool success = false;
	
	if (!output)
	{
		*output = false;
	}

	success = false;
	
	if (!reader)
	{
		return success;
	}

	if (reader->type == ZRDR_ARRAY && reader->array->integer > 1)
	{
		reader = reader->array;
	}

	if (reader->type == ZRDR_INTEGER)
	{
		if (reader->integer == 0)
		{
			*output = false;
			success = true;
		}
		else
		{
			*output = true;
			success = true;
		}
	}
	else
	{
		success = false;
		if (reader->type == ZRDR_STRING)
		{
			if (strcasecmp(reader->string, "true") == 0 || strcasecmp(reader->string, "on"))
			{
				*output = true;
				success = true;
			}
			else if (strcasecmp(reader->string, "false") == 0 || strcasecmp(reader->string, "off"))
			{
				*output = false;
				success = true;
			}
		}
	}
	
	return success;
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