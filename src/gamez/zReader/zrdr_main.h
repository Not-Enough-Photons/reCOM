#pragma once
#include <iostream>
#include <cstdint>

#include "gamez/zUtil/util_stable.h"
#include "gamez/zArchive/zar.h"

class _zrdr;
class CRdrFile;

enum ZRDR_TYPE
{
	ZRDR_NULL,
	ZRDR_INTEGER,
	ZRDR_REAL,
	ZRDR_STRING,
	ZRDR_ARRAY
};

int cur_zrdr_flags = 0;
char* cur_zrdr_path = '\0';

_zrdr* zrdr_read(const char* reader, const char* path, int dummy);
char* zrdr_findfile(const char* file, const char* path);
int zrdr_free(CRdrFile* reader);
void zrdr_freearray(_zrdr* array);
void _resolveA(_zrdr* reader, _zrdr* other, int count);
void _resolveB(_zrdr* reader, _zrdr* other, int count);

char* zrdr_findstring(_zrdr* reader, const char* tag);
bool zrdr_findint(_zrdr* reader, const char* tag, int* output, int iterations);
bool zrdr_finduint(_zrdr* reader, const char* tag, unsigned int* output, int iterations);
bool zrdr_findreal(_zrdr* reader, const char* tag, float* output, int iterations);
bool zrdr_findbool(_zrdr* reader, const char* tag, bool* output);
_zrdr* zrdr_findtag(_zrdr* reader, const char* tag);
_zrdr* zrdr_findtag_startidx(_zrdr* reader, const char* tag, int iterations);

bool zrdr_toINT(_zrdr* reader, int* output, int size);
bool zrdr_tobool(_zrdr* reader, bool* output);

_zrdr* _zrdr_nexttag(_zrdr* reader, const char* tag, size_t size, _zrdr* other);

typedef struct _zrdr
{
	_zrdr(); 
	_zrdr(const _zrdr* other, const CSTable* table);
	~_zrdr();

	bool IsArray() const;
	void Clone(const _zrdr* other, const CSTable* table);
	int GetInt() const;
	char* Get(int offset) const;

	ZRDR_TYPE type;
	bool isclone;
	bool packed;

	int unused;

	int length;

	union
	{
		float real;
		int integer;
		char* string;
		_zrdr* array;
	};
};

typedef struct CRdrFile : public _zrdr
{
	CRdrFile();
	~CRdrFile();

	static CRdrFile* Load(zar::CZAR* archive, zar::CKey* key);
	static bool ValidateFormat();

	zar::CKey* Insert(zar::CZAR* archive, zar::CKey* key);
	_zrdr* MakeUnion(const char* name, bool createString);
	char ReadToken(_zrdr** readerArray, _zrdr** unionArray);

	CSTable m_strings;
	void* m_buffer;
	size_t m_size;
};

class CRdrArchive : public zar::CZAR
{
public:
	static std::list<zar::CZAR*> m_list;

	static zar::CZAR* AddArchive(const char* name, const char* path);
	static bool RemoveArchive(const char* name, const char* path);

	static CRdrFile* FindRdr(const char* reader);

	static void OpenAll();
	static void CloseAll();
};
