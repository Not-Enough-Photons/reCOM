#pragma once
#include "zrdr.h"

#include <ctype.h>

#define zrdr_alloc(count, size) (_zrdr*)zcalloc(count, size)

bool _NeedQuotes(_zrdr* reader);
bool _OutputASCII(FILE* out, _zrdr* reader, s32 offset);

class CRdrEditor
{
public:
	CRdrEditor();
	~CRdrEditor();
public:
	int push(const char* str);
	int pop();

	int addint(const char* tag, s32 value);
	int addintnode(const char* tag, s32 value);
	int addSTRING(const char* tag, const char* value);
};