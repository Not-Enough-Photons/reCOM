#pragma once
#include "util_systemio.h"

extern bool dumpLog;

class COutput;

extern COutput* debug;

void zUtilInit(const char* log);

class COutput
{
public:
	COutput(const char* log, bool doLog);

	static void DumpLog(const char* file);
private:
	bool m_doLog;
	CFileIO* m_fileIO;
};