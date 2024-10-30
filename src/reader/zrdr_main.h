#pragma once
#include <iostream>
#include <cstdint>

#include "util/util_stable.h"

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

class _zrdr
{
public:
	_zrdr(); 
	_zrdr(const _zrdr* other, const CSTable* table);

	void Clone(const _zrdr* other, const CSTable* table);
private:
	ReaderType type;
	_zrdr* next;
};

_zrdr* zrdr_read(const char* reader, const char* path, int dummy);
void zrdr_free(_zrdr* reader);

_zrdr* zrdr_findtag(const char* tag);
_zrdr* zrdr_findtag_startidx(const char* tag, int iterations);

bool zrdr_findint(_zrdr* reader, const char* tag, int* output, int iterations);
bool zrdr_findreal(_zrdr* reader, const char* tag, float* output, int iterations);
bool zrdr_findbool(_zrdr* reader, const char* tag, bool* output);

inline char* GetMode(OpenFlags mode)
{
	switch (mode)
	{
	case OpenFlags::READ:
		return "r";
	case OpenFlags::WRITE:
		return "w";
	case OpenFlags::READWRITE:
		return "rw";
	case OpenFlags::APPEND:
		return "a";
	case OpenFlags::CREATE:
	case OpenFlags::TRUNCATE:
		return "w+";
	case OpenFlags::EXCLUDE:
		return "w+x";
	}

	return 0;
}

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

class CRdrArchive : public CRdrIO
{
public:
	static int GetReaderHashDifference(unsigned char parentByte, unsigned char childByte);
	static int EntryLookup(const char* parentReader, const char* childReader);
};
