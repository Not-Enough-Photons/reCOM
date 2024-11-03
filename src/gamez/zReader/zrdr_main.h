#pragma once
#include <iostream>
#include <cstdint>

#include "gamez/zUtil/util_stable.h"
#include "gamez/zArchive/zar.h"

class _zrdr;

#define cast_rdr_array(type) reinterpret_cast<_zrdr*>(type)
#define cast_rdr_int(type) static_cast<int>(type)
#define cast_rdr_float(type) static_cast<float>(type)
#define cast_rdr_double(type) static_cast<double>(type)

enum ReaderType
{
	TYPE_NULL,
	TYPE_REFERENCE,
	TYPE_VALUE,
	TYPE_TAG,
	TYPE_ARRAY
};

enum OpenFlags
{
	READ		= 0x0001,
	WRITE		= 0x0002,
	READWRITE	= 0x0003,
	APPEND		= 0x0100,
	CREATE		= 0x0200,
	TRUNCATE	= 0x0400,
	EXCLUDE     = 0x1000
};

typedef void* zrdr_type;

_zrdr* zrdr_read(const char* reader, const char* path, int dummy);
_zrdr* zrdr_findtag(const char* tag);
_zrdr* zrdr_findtag_startidx(const char* tag, int iterations);

class _zrdr
{
public:
	friend void zrdr_free(_zrdr* reader);
	friend void zrdr_freearray(_zrdr* array);
	friend void _resolveA(_zrdr* reader, _zrdr* other, int count);
	friend void _resolveB(_zrdr* reader, _zrdr* other, int count);

	friend bool zrdr_findint(_zrdr* reader, const char* tag, int* output, int iterations);
	friend bool zrdr_findreal(_zrdr* reader, const char* tag, float* output, int iterations);
	friend bool zrdr_findbool(_zrdr* reader, const char* tag, bool* output);

public:
	_zrdr(); 
	_zrdr(const _zrdr* other, const CSTable* table);

	void Clone(const _zrdr* other, const CSTable* table);
private:
	ReaderType type;
	zrdr_type value;
};

class CRdrFile : private _zrdr
{
public:
	CRdrFile();
	~CRdrFile();

	static CRdrFile* Load(zar::CZAR* archive, zar::CKey* key);
	static bool ValidateFormat();

	zar::CKey* Insert(zar::CZAR* archive, zar::CKey* key);
	_zrdr* MakeUnion(const char* name, bool createString);
	char ReadToken(_zrdr** readerArray, _zrdr** unionArray);
private:
	void* block;
	size_t blockSize;
};

class CIO
{
public:
	CIO();
	~CIO();

	virtual void Init() { }
};

class CFileIO : public CIO
{
public:
	CFileIO();
	~CFileIO();

	bool Open(char* file, OpenFlags flags);
	// void Open(...);
	void LoadBuffer();
	virtual void Release();
	OpenFlags GetMode() const;
	bool IsOpen();
	char* PS2FileName(char* file, char* directory, int param_3);

	virtual void fflush();
	virtual int fread();
	// virtual void fread(...);
	virtual void freadchar();
	virtual void fseek();
	virtual void ftell();
	virtual int fwrite(const void* buf, int count);
	// virtual void fwrite(...);
protected:
	OpenFlags flags;
	int position;
private:
	const char* m_root_path = "host0:.\\";
	static bool m_write_status;

	FILE* file;
};

class CBufferIO : public CFileIO
{
public:
	CBufferIO();
	~CBufferIO();

	int fwrite(const void* buf, int count);
	int fseek(int offset, int origin);
private:
	int field14_0x14;
	int field15_0x18;
	int field16_0x1c;
	int field13_0x10;
	int is_open;
};

class CRdrIO : public CFileIO
{

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
