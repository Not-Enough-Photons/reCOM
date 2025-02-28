#define STB_IMAGE_IMPLEMENTATION
#include "hud.h"

#include <SDL3_image/SDL_image.h>
#include <stb/stb_image.h>

#include "gamez/zAssetLib/zassetlib.h"
#include "gamez/zSave/zsave.h"
#include "gamez/zVideo/zvid.h"

bool flipped = false;

extern zar::CZAR texarchive;
extern zar::CZAR palarchive;

extern const char* dir;

CLetterBox* letterbox;
CZPauseTest* pausemenu;
C2DString* strings;
u32 num_strings;
u32 num_bitmaps;
C2DBitmap* bitmaps;

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
    letterbox = new CLetterBox();
    pausemenu = new CZPauseTest();
    pausemenu->ReInit();
    letterbox->AddLetterbox();
    
    return true;
}

void CTestState::Tick(f32 dT)
{
    SDL_Event e;
    SDL_PollEvent(&e);
    
    SDL_SetRenderDrawColor(theWindow->GetRenderer(), 15, 15, 15, 255);
    SDL_RenderClear(theWindow->GetRenderer());
    
    letterbox->Tick(dT * 10);
    letterbox->Draw(NULL);
    pausemenu->Draw(NULL);

    SDL_RenderPresent(theWindow->GetRenderer());
}