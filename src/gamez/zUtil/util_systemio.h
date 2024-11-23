#pragma once
#include <iostream>

enum OpenFlags
{
	NONE = 0,
	READ = 0x0001,
	WRITE = 0x0002,
	READWRITE = 0x0003,
	APPEND = 0x0100,
	CREATE = 0x0200,
	TRUNCATE = 0x0400,
	EXCLUDE = 0x1000
};

struct _FILECD
{
	char* name;
	unsigned int startSector;
	unsigned int endSector;
	unsigned int sectorSize;
};

class CFileCD
{
public:
	static int BuildTOC();
	static char* CreatePath(const char* dir, const char* path);
	static _FILECD* Find(const char* file);
	static size_t Read(void* buf, int count);
public:
	static _FILECD* m_TOC;

	_FILECD* m_toc;
	unsigned int m_pos;
	int m_headSector;
	char* m_sector;
	char* m_buf;
};

class CIO
{
public:
	CIO();
	~CIO();

	virtual void Init() {}

	virtual size_t fread(int offset, void** buf);
	virtual size_t fread(void* buf, size_t size);
	virtual size_t fwrite(char* buf);
	virtual size_t fwrite(void* buf, size_t size);

	virtual int fseek(int offset, int origin);
	virtual int ftell(int* fd);

	virtual void fflush();
};

class CFileIO : public CIO
{
public:
	CFileIO();
	CFileIO(const CFileIO& other);
	~CFileIO();

	static void SetRootPath(const char* rootPath);

	static const char* m_root_path;
	static bool m_write_status;
public:
	bool Open(const char* file, unsigned int mode);
	void Close();
	char* PS2FileName(const char* file, char* directory, int depth);

	virtual bool IsOpen();
	virtual void Release();

	virtual size_t fread(int offset, void** buf);
	virtual size_t fread(void* buf, size_t size);
	virtual size_t fwrite(char* buf);
	virtual size_t fwrite(const void* buf, size_t size);

	virtual int fseek(int offset, int origin);
	virtual int ftell(int* fd);

	virtual void fflush();

	unsigned int GetMode() const;
	int GetSize() const;
protected:
	int m_file;
	CFileCD* m_cd;
	int m_filesize;
	unsigned int m_mode;
};

class CBufferIO : public CFileIO
{
public:
	CBufferIO() : CFileIO() { }
	CBufferIO(const CBufferIO& other);
	~CBufferIO();

	bool LoadBuffer();

	virtual bool Open(void* buf, unsigned int mode);
	virtual void Close();
	virtual void Release();

	virtual bool IsOpen();

	virtual size_t fread(int offset, void** buf);
	virtual size_t fread(void* buf, size_t size);
	virtual char freadchar(char* buf);
	virtual size_t fwrite(char* buf);
	virtual size_t fwrite(void* buf, size_t size);

	virtual int fseek(int offset, int origin);
	virtual int ftell(int* fd);
};