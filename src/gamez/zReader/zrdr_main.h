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

class _zrdr
{
public:
	friend void zrdr_freearray(_zrdr* array);
	friend void _resolveA(_zrdr* reader, _zrdr* other, int count);
	friend void _resolveB(_zrdr* reader, _zrdr* other, int count);

	friend bool zrdr_findint(_zrdr* reader, const char* tag, int* output, int iterations);
	friend bool zrdr_findreal(_zrdr* reader, const char* tag, float* output, int iterations);
	friend bool zrdr_findbool(_zrdr* reader, const char* tag, bool* output);
	friend _zrdr* zrdr_findtag(_zrdr* reader, const char* tag);
	friend _zrdr* zrdr_findtag_startidx(_zrdr* reader, const char* tag, int iterations);

public:
	_zrdr(); 
	_zrdr(const _zrdr* other, const CSTable* table);
	~_zrdr();

	bool IsArray() const;
	void Clone(const _zrdr* other, const CSTable* table);
	int GetInt() const;
	char* Get(int offset) const;
public:
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

class CRdrFile : public _zrdr
{
	friend int zrdr_free(CRdrFile* reader);
public:
	CRdrFile();
	~CRdrFile();

	static CRdrFile* Load(zar::CZAR* archive, zar::CKey* key);
	static bool ValidateFormat();

	zar::CKey* Insert(zar::CZAR* archive, zar::CKey* key);
	_zrdr* MakeUnion(const char* name, bool createString);
	char ReadToken(_zrdr** readerArray, _zrdr** unionArray);
private:
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
