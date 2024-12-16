#pragma once
#include "gamez/zReader/zrdr.h"

#define string_exists(x) (x != (char*)0)

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
void zUtilUninit();