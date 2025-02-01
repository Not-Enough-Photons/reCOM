#include <GL/glew.h>

#include <SDL3_image/SDL_image.h>

#include "gamez/zFTS/fts_state.h"
#include "gamez/zFTS/zfts.h"

bool LoadWorld(const char* db);

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    // CSnd::Init();

    LoadWorld("ui");
    
    return true;
}

void CTestState::Tick(f32 dT)
{
    // zVid_Swap(true);
    // CZIMGUI::Tick(dT);
    // SDL_RenderClear(theWindow->GetRenderer());
}
