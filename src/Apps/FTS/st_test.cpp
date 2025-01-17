#include "gamez/zFTS/fts_state.h"
#include "gamez/zReader/zrdr.h"

const char* path = "D:/RUN/READERC.ZAR";

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    CRdrArchive::AddArchive(path, NULL);
    CRdrArchive::OpenAll();
    _zrdr* reader = CRdrArchive::FindRdr("motion.rdr");
    CRdrArchive::CloseAll();
    return true;
}
