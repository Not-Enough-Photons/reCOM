#include <GL/glew.h>

#include "gamez/zEntity/zentity.h"
#include "gamez/zFTS/fts_state.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zReader/zrdr_local.h"
#include "gamez/zVideo/zvid.h"

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    const char* path = "D:/run/ui/assetlib/ui2d/ui2d_txr.zed";
    zar::CZAR archive = zar::CZAR(NULL, NULL);
    if (!archive.Open(path, 1, 0, 16))
    {
        theTerminal.Print("Archive read failed!", 128);
        theTerminal.Render();
        return false;
    }

    
    
    return true;
}

void CTestState::Tick(f32 dT)
{
    zVid_Swap(true);
    SDL_Event e;
    SDL_PollEvent(&e);
}
