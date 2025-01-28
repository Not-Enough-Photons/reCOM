#include <GL/glew.h>

#include <SDL3_image/SDL_image.h>

#include "gamez/zEntity/zentity.h"
#include "gamez/zFTS/fts_state.h"
#include "gamez/zIMGUI/zimgui.h"
#include "gamez/zVideo/zvid.h"
#include "gamez/zTexture/ztex.h"

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    const char* path = "E:/RUN/COMMON/ASSETLIB/HUD/HUD_TXR.ZED";
    zar::CZAR archive = zar::CZAR(NULL, NULL);
    if (!archive.Open(path, 1, 0, 16))
    {
        theTerminal.Print("Archive read failed!", 128);
        theTerminal.Render();
        return false;
    }

    auto texkey = archive.OpenKey("textures");
    auto key = archive.OpenKey("action_tune_offense.tif");
    
    zdb::CTexture texture = zdb::CTexture(key->GetName());
    texture.Read(archive);

    archive.CloseKey(key);
    archive.Close();
    
    SDL_Renderer* renderer = theWindow->GetRenderer();
    
    // SDL_Surface* surface = IMG_LoadTIF_IO(SDL_IOFromMem(texture.m_buffer, texture.m_size));
    SDL_Surface* surface = SDL_CreateSurfaceFrom(texture.m_width, texture.m_height, SDL_PIXELFORMAT_ABGR8888, texture.m_buffer, texture.m_width * (sizeof(u8) * 4));

    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
        return false;
    }
		
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);

    if (!tex)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
        return false;
    }

    SDL_FRect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = texture.m_width;
    rect.h = texture.m_height;

    // zVid_ClearColor(0.0f, 0.0f, 0.0f);
    SDL_RenderTexture(renderer, tex, NULL, &rect);

    SDL_DestroySurface(surface);
    
    return true;
}

void CTestState::Tick(f32 dT)
{
    zVid_ClearColor(0.0f, 0.0f, 0.0f);
    // zVid_Swap(true);
    CZIMGUI::Tick(dT);
    SDL_RenderClear(theWindow->GetRenderer());
}
