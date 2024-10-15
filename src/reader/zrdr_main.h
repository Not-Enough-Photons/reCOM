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

};

class CFileIO : public CIO
{
public:
	CFileIO();
};

class CBufferIO : public CFileIO
{

};

class CRdrIO : public CFileIO
{
public:
	static CZAREntry* GetRootEntry(CZAREntry* entry, const char* name);
	static CZAREntry* GetRootEntry(CZAREntry* entry, const char* name, int it);
	static CZAREntry* ReadRoot(CZAREntry* entry, const char* name);
};

class CRdrArchive : public CRdrIO
{
public:
	static int GetReaderHashDifference(unsigned char parentByte, unsigned char childByte);
	static int EntryLookup(const char* parentReader, const char* childReader);
};
