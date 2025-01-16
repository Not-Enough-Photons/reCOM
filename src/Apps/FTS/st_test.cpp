#include "gamez/zFTS/fts_state.h"
#include "gamez/zReader/zrdr.h"

const char* path = "D:/Misc/Media/Games/PS2/SOCOM/SOCOM 1/SOCOM - May 2002/RUN/READERC.ZAR";

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    CRdrArchive::AddArchive(path, NULL);
    CRdrArchive::OpenAll();
    _zrdr* reader = CRdrArchive::FindRdr("ai_common.rdr");
    CRdrArchive::CloseAll();
    return true;
}
