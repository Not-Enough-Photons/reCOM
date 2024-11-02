#include "util_main.h"

COutput::COutput(const char* outputLogPath)
{
	m_outStream = new CFileIO();
}

void zUtilInit(const char* outputLogPath)
{
	s_Output = new COutput(outputLogPath);
}

void zUtilUninit()
{
	delete s_Output;
	s_Output = NULL;
}