#pragma once
#include "reader/zrdr_main.h"

class COutput
{
public:
	COutput(const char* outputLogPath);
	~COutput();
private:
	CFileIO* m_outStream;
};

static COutput* s_Output;

void zUtilInit(const char* outputLogPath);