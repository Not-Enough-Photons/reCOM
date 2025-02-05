#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_pixels.h>

#include <stb/stb_image.h>

#include "gamez/zFTS/fts_state.h"
#include "gamez/zFTS/zfts.h"
#include "gamez/zIMGUI/zimgui.h"
#include "gamez/zReader/zrdr_local.h"
#include "gamez/zVideo/zvid.h"

bool flipped = false;

extern zar::CZAR texarchive;
extern zar::CZAR palarchive;

extern const char* dir;

bool LoadWorld(const char* db);

extern bool LoadTexture(zdb::CTexture texture)
{
    return true;
}

extern bool LoadPalette(zdb::CTexPalette palette)
{
    return true;
}

extern void LoadZAR()
{
    texarchive.Open(dir, 1, 0, 16);
}

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    return true;
}

void CTestState::Tick(f32 dT)
{
    SDL_RenderClear(theWindow->GetRenderer());
    SDL_SetRenderDrawColor(theWindow->GetRenderer(), 15, 15, 15, 255);
    CZIMGUI::Tick(dT);
    SDL_RenderPresent(theWindow->GetRenderer());
}