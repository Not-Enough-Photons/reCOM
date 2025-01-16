#include "gamez/zFTS/fts_state.h"
#include "gamez/zReader/zrdr.h"

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    return true;
}
