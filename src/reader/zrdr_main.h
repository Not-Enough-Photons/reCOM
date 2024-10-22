#pragma once
#include <iostream>
#include <cstdint>

enum ZEntryDescriptor
{
	END,
	NONE,
	VALUE,
	STRING,
	FOLDER
};

typedef struct CZAREntry
{
	ZEntryDescriptor descriptor;
	uint16_t			entries;
	CZAREntry*			next;
};

struct zrdr
{
	char type;
	zrdr* next;
};

zrdr* zrdr_findtag(zrdr* reader, const char* tag);
zrdr* zrdr_findtag_startidx(zrdr* reader, const char* tag, int iterations);
bool zrdr_findreal(zrdr* reader, const char* tag, float* output, int iterations);

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
	virtual void Release();
private:
	int field4_0x4;
};

class CBufferIO : public CFileIO
{
public:
	CBufferIO();
	~CBufferIO();

	void Open();
	// void Open(...);
	void Release();
	void LoadBuffer();
	bool IsOpen();

	void fflush();
	void fread();
	// void fread(...);
	void freadchar();
	void fseek();
	void ftell();
	void fwrite();
	// void fwrite(...);
private:
	int field14_0x14;
	int field15_0x18;
	int field16_0x1c;
	int field13_0x10;
	bool is_open = false;
};

class CRdrIO : public CFileIO
{
public:
	static CZAREntry*  zrdr_findtag           (CZAREntry* entry, const char* name);
	static CZAREntry*  zrdr_findtag_startidx  (CZAREntry* entry, const char* name, int it);
	static CZAREntry*  ReadRoot               (CZAREntry* entry, const char* name);
	static void*       zrdr_findbool          (CZAREntry* entry, const char* name, int param_3);
	static int         zrdr_readstring        (CZAREntry* entry, const char* name, void* buf);
	static int         zrdr_readreal          (CZAREntry* entry, const char* name, float* output, int maxDepth);
	static int         zrdr_readint           (CZAREntry* entry, const char* name, int* output, int maxDepth);

	static void        ReadZAmmo              (void* param_1, CZAREntry* entry);
	static void        ReadZWeapon            (void* param_1, CZAREntry* entry);
};

class CRdrArchive : public CRdrIO
{
public:
	static int GetReaderHashDifference(unsigned char parentByte, unsigned char childByte);
	static int EntryLookup(const char* parentReader, const char* childReader);
};
