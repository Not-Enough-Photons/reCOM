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

class CFileCD
{
public:
	static int BuildTOC();
	static char* CreatePath(const char* dir, const char* path);
	static int Find(const char* file);
	static int* Read(void* buf, int count);
};

class CIO
{
public:
	CIO();
	~CIO();

	virtual void Init() {}
};

class CFileIO : public CIO
{
public:
	CFileIO();
	~CFileIO();

	static void SetRootPath(const char* rootPath);

	static const char* m_root_path;
	static bool m_write_status;
public:
	bool Open(char* file, OpenFlags flags);
	void Close();
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
	int m_file;
	CFileCD* m_cd;
	int m_filesize;
	OpenFlags m_mode;
};

class CBufferIO : public CFileIO
{
public:
	CBufferIO() : CFileIO() { }
	~CBufferIO();

	void Close();

	int fwrite(const void* buf, int count);
	int fseek(int offset, int origin);
};