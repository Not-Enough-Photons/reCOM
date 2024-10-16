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
	/// <summary>
	/// Finds a ZAR tag inside a list.
	/// </summary>
	/// <param name="entry">The base.</param>
	/// <param name="name">The name of the tag you want to find.</param>
	/// <returns>The tag.</returns>
	static CZAREntry*  zrdr_findtag(CZAREntry* entry, const char* name);
	static CZAREntry*  zrdr_findtag_startidx(CZAREntry* entry, const char* name, int it);
	static CZAREntry*  ReadRoot    (CZAREntry* entry, const char* name);
	static int         ReadString  (CZAREntry* entry, const char* name, void* buf);
	static int         ReadFloat   (CZAREntry* entry, const char* name, float* output, int maxDepth);
	static int         ReadInt     (CZAREntry* entry, const char* name, int* output, int maxDepth);

	static void        ReadZAmmo   (void* param_1, CZAREntry* entry);
	static void        ReadZWeapon (void* param_1, CZAREntry* entry);
};

class CRdrArchive : public CRdrIO
{
public:
	static int GetReaderHashDifference(unsigned char parentByte, unsigned char childByte);
	static int EntryLookup(const char* parentReader, const char* childReader);
};
