#include <GL/glew.h>

#include <SDL3_image/SDL_image.h>

#include "gamez/zEntity/zentity.h"
#include "gamez/zFTS/fts_state.h"
#include "gamez/zIMGUI/zimgui.h"
#include "gamez/zSound/zsnd.h"
#include "gamez/zVideo/zvid.h"

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    CSnd::Init();
    return true;
}

void CTestState::Tick(f32 dT)
{
    // zVid_Swap(true);
    CZIMGUI::Tick(dT);
    SDL_RenderClear(theWindow->GetRenderer());
}
