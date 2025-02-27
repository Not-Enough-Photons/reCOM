#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_pixels.h>

#include <stb/stb_image.h>

#include "hud.h"
#include "gamez/zFTS/fts_state.h"
#include "gamez/zFTS/zfts.h"
#include "gamez/zIMGUI/zimgui.h"
#include "gamez/zReader/zrdr_local.h"
#include "gamez/zVideo/zvid.h"

bool flipped = false;

extern zar::CZAR texarchive;
extern zar::CZAR palarchive;

extern const char* dir;

CLetterBox* letterbox;
CZPauseTest* pausemenu;
C2DString strings[8];

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
    letterbox->AddLetterbox();
    pausemenu = new CZPauseTest();
    pausemenu->ReInit();

    auto reader = zrdr_read("./data/zrdr/test_text.rdr", NULL, 0);

    for (u32 i = 1; reader->array->integer; i++)
    {
        auto node = &reader->array[i];
        PNT3D color;
        PNT2D position;
        
        char* text = zrdr_findstring(node, "text");
        zrdr_findPNT3D(node, "color", &color);
        zrdr_findPNT2D(node, "position", &position);

        strings[i].Load(text, NULL, 250, 250 * i - 0.25f);
        strings[i].m_color.x = color.x;
        strings[i].m_color.y = color.y;
        strings[i].m_color.z = color.z;
    }
    
    zrdr_free(reader);
    return true;
}

void CTestState::Tick(f32 dT)
{
    SDL_Event e;
    SDL_PollEvent(&e);
    SDL_SetRenderDrawColor(theWindow->GetRenderer(), 15, 15, 15, 255);
    SDL_RenderClear(theWindow->GetRenderer());
    // letterbox->Tick(dT);
    // letterbox->Draw(NULL);
    // pausemenu->Draw(NULL);

    for (u32 i = 0; i < 2; i++)
    {
        strings[i].Draw(NULL);
    }
    
    SDL_RenderPresent(theWindow->GetRenderer());
}