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

	void Release();
private:
	int field14_0x14;
	int field15_0x18;
	int field16_0x1c;
	int field13_0x10;
};

class CRdrIO : public CFileIO
{
public:
	static CZAREntry*  zrdr_findtag           (CZAREntry* entry, const char* name);
	static CZAREntry*  zrdr_findtag_startidx  (CZAREntry* entry, const char* name, int it);
	static CZAREntry*  ReadRoot               (CZAREntry* entry, const char* name);
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
