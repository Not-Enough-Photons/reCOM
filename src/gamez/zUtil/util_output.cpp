#include "zutil.h"

COutput* debug;

bool dumpLog = true;

void zUtilInit(const char* log)
{
	debug = new COutput(log, false);
}

COutput::COutput(const char* file, bool doLog)
{
	m_doLog = doLog;
	m_fileIO = new CFileIO();

	if (file != NULL)
	{
		m_fileIO->Open(file);
	}
}

void COutput::DumpLog(const char* file)
{
	return;
}