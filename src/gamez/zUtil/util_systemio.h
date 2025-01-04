#pragma once
#include <iostream>

#define S_IXOTH 0x0001
#define S_IWOTH 0x0002
#define S_IROTH 0x0004
#define S_IRWXO 0x0007
#define S_IXGRP 0x0010
#define S_IWGRP 0x0020
#define S_IRGRP 0x0040
#define S_IRWXG 0x0070
#define S_IXUSR 0x0100
#define S_IWUSR 0x0200
#define S_IRUSR 0x0400
#define S_IRWXU 0x0700

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
	virtual void Init() {}
	virtual bool Open(void* buf) { return false; }
	virtual bool Open(const char* buf) { return false; }
	virtual void Close() {}

	virtual bool IsOpen() const { return false; }
	virtual unsigned int GetMode() const { return m_mode; }
	virtual size_t GetSize() const { return m_filesize; }

	virtual size_t fread(int offset, void** buf) { return 0; }
	virtual size_t fread(void* buf, size_t size) { return 0; }
	virtual size_t fwrite(const char* buf);
	virtual size_t fwrite(const void* buf, size_t size) { return 0; }

	virtual size_t fseek(int offset, int origin) { return 0; }
	virtual size_t ftell() { return 0; }

	virtual void fflush() {}
public:
	int64_t m_file;
	size_t m_filesize;
	unsigned int m_mode;
};

class CFileIO : public CIO
{
public:
	CFileIO();
	CFileIO(const CFileIO& other);

	static void SetRootPath(const char* rootPath);

	static const char* m_root_path;
	static bool m_write_status;
public:
	virtual void Init() {}
	virtual bool Open(void* buf) { return false; }
	virtual bool Open(const char* file);
	virtual void Close();
	virtual void Release();

	virtual bool IsOpen() const;
	virtual unsigned int GetMode() const;
	virtual size_t GetSize() const;

	virtual size_t fread(int offset, void** buf);
	virtual size_t fread(void* buf, size_t size);
	virtual size_t fwrite(const char* buf);
	virtual size_t fwrite(const void* buf, size_t size);

	virtual size_t fseek(int offset, int origin);
	virtual size_t ftell();

	virtual void fflush();

protected:
	CFileCD* m_cd;
};

class CBufferIO : public CFileIO
{
public:
	CBufferIO();
	CBufferIO(const CBufferIO& other);

	void CopyFileIO(const CFileIO* io);
	bool LoadBuffer();

	virtual bool Open(void* buf, size_t size);
	virtual bool Open(const char* buf);
	virtual void Close();
	virtual void Release();

	virtual bool IsOpen() const { return m_buffer != NULL; }

	virtual size_t fread(int offset, void** buf);
	virtual size_t fread(void* buf, size_t size);
	virtual char freadchar(char* buf) { return 0; }
	virtual size_t fwrite(const char* buf) { return 0; }
	virtual size_t fwrite(const void* buf, size_t size) { return 0; }

	virtual size_t fseek(int offset, int origin);
	virtual size_t ftell();
private:
	void* m_buffer;
	size_t m_bufsize;
};