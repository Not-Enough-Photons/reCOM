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
C2DString* strings;
u32 num_strings;

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
    auto test_text = zrdr_findtag(reader, "test_text");

    if (test_text->array->integer > 1)
    {
        num_strings = test_text->array->integer;
        strings = new C2DString[num_strings];
    }
    
    for (u32 i = 0; i < test_text->array->integer - 1; i++)
    {
        auto node = &test_text->array[i + 1];
        PNT3D color;
        PNT2D position;
        f32 scale;
        
        char* text = zrdr_findstring(node, "text");
        zrdr_findPNT3D(node, "color", &color);
        zrdr_findPNT2D(node, "position", &position);
        zrdr_findreal(node, "scale", &scale, 1);

        strings[i].m_scale = scale;
        strings[i].Load(text, NULL, position.x, position.y);
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

    for (u32 i = 0; i < num_strings; i++)
    {
        strings[i].Draw(NULL);
    }
    
    SDL_RenderPresent(theWindow->GetRenderer());
}