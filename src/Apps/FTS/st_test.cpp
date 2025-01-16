#include "gamez/zFTS/fts_state.h"
#include "gamez/zReader/zrdr.h"

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    _zrdr reader;
    _zrdr real;
    reader.type = ZRDR_ARRAY;
    real.type = ZRDR_REAL;

    reader.array = &real;
    real.real = 1.0f; // 0x3f800000
    return true;
}
