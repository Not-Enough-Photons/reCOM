#pragma once
#include <iostream>
#include <cstdint>

#include "gamez/zArchive/zar.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zUtil/util_stable.h"

#define MAX_ZRDR_PATH_LEN 767

#define pptoken_ifdef 0 
#define pptoken_else 1
#define pptoken_endif 2
#define pptoken_include 3
#define pptoken_undef 4

struct _zrdr;
class CRdrFile;

enum ZRDR_TYPE
{
	ZRDR_NULL,
	ZRDR_INTEGER,
	ZRDR_REAL,
	ZRDR_STRING,
	ZRDR_ARRAY
};

extern s32 cur_zrdr_flags;
extern char* cur_zrdr_path;
extern std::list<char*> zrdr_symbols;

void _resolveA(_zrdr* reader, const _zrdr* other, const char* tag);
void _resolveB(_zrdr* reader, const _zrdr* other, const char* tag);
int _get_pptoken(char* token);
bool _preproc_filter(char* token, bool param_2);
bool _eval_defined(char* token);

_zrdr* zrdr_read(const char* reader, const char* path, s32 dummy);
const char* zrdr_findfile(const char* file, const char* path);
s32 zrdr_free(CRdrFile* reader);
void zrdr_freearray(_zrdr* array);
void _resolveA(_zrdr* reader, const _zrdr* other, s32 count);
void _resolveB(_zrdr* reader, const _zrdr* other, s32 count);

char* zrdr_findstring(_zrdr* reader, const char* tag);
bool zrdr_findint(_zrdr* reader, const char* tag, s32* output, s32 iterations);
bool zrdr_finduint(_zrdr* reader, const char* tag, u32* output, s32 iterations);
bool zrdr_findreal(_zrdr* reader, const char* tag, f32* output, s32 iterations);
bool zrdr_findbool(_zrdr* reader, const char* tag, bool* output);
_zrdr* zrdr_findtag(_zrdr* reader, const char* tag);
_zrdr* zrdr_findtag_startidx(_zrdr* reader, const char* tag, s32 iterations);

bool zrdr_toINT(_zrdr* reader, s32* output, s32 size);
bool zrdr_tobool(_zrdr* reader, bool* output);

_zrdr* _zrdr_nexttag(_zrdr* reader, const char* tag, size_t size, _zrdr* other);

struct _zrdr
{
	_zrdr();

	bool IsArray() const;
	void Clone(const _zrdr* other, const CSTable* table);
	int GetInt() const;
	char* Get(int offset) const;

	u32 type : 8;
	u32 isclone : 1;
	u32 packed : 1;
	u32 unused : 6;
	u32 length : 16;
	
	union
	{
		f32 real;
		s32 integer;
		char* string;
		_zrdr* array;
	};
};

class CRdrFile : public _zrdr
{
public:
	CRdrFile();

	static CRdrFile* Load(zar::CZAR* archive, zar::CKey* key);
	static bool Resolve(CRdrFile* file, bool resolveA);

	zar::CKey* Insert(zar::CZAR* archive, zar::CKey* key);
	_zrdr* MakeUnion(const char* name, bool createString);
	char ReadToken(_zrdr** readerArray, _zrdr** unionArray);
	CRdrFile* ReadArray();

	bool ValidateFormat() { return false; }

	CSTable m_strings;
	char* m_buffer;
	u32 m_size;
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
