#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_pixels.h>

#include <stb/stb_image.h>

#include "gamez/zFTS/fts_state.h"
#include "gamez/zFTS/zfts.h"
#include "gamez/zIMGUI/zimgui.h"
#include "gamez/zVideo/zvid.h"

bool flipped = false;

extern zar::CZAR texarchive;
extern zar::CZAR palarchive;

extern const char* dir;

bool LoadWorld(const char* db);

struct Preview
{
    SDL_FRect rect;
    SDL_Texture* texture;
    SDL_Surface* surface;
};

Preview preview;

SDL_Palette* pal = SDL_CreatePalette(8);
SDL_Color default_pal_colors[8] =
{
    SDL_Color { 255, 255, 255, 255},
    SDL_Color { 100, 100, 100, 100 },
    SDL_Color { 0, 0, 0, 255 },
};

extern bool LoadTexture(zdb::CTexture texture)
{
    preview.texture = NULL;
    
    SDL_Renderer* renderer = theWindow->GetRenderer();

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    if (preview.surface)
    {
        SDL_DestroySurface(preview.surface);
        preview.surface = NULL;
    }
    
    preview.surface = SDL_CreateSurface(texture.m_width, texture.m_height, SDL_PIXELFORMAT_RGBA32);
    
    u8* tex_ptr = (u8*)texture.m_buffer;

    for (u32 y = 0; y < texture.m_height; y++)
    {
        for (u32 x = 0; x < texture.m_width; x++)
        {
            SDL_Color col = pal->colors[*tex_ptr++];
            SDL_WriteSurfacePixel(preview.surface, x, y, col.r, col.g, col.b, col.a);
        }
    }

    SDL_FlipSurface(preview.surface, SDL_FLIP_VERTICAL);
    
    preview.texture = SDL_CreateTextureFromSurface(renderer, preview.surface);
    
    if (!preview.texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
        return false;
    }

    SDL_RenderTexture(renderer, preview.texture, NULL, NULL);
    
    SDL_FRect rect;
    rect.x = (zVid.renderWidth / 2) - (texture.m_width / 2);
    rect.y = (zVid.renderHeight / 2) - (texture.m_height / 2);
    rect.w = texture.m_width;
    rect.h = texture.m_height;

    preview.rect = rect;
}

extern bool LoadPalette(zdb::CTexPalette palette)
{
    if (pal)
    {
        SDL_DestroyPalette(pal);
    }
    
    std::vector<SDL_Color> colors;

    u32 i = 0;
    u8* ptr = (u8*)palette.m_buffer;

    while (i < palette.m_size)
    {
        u8 r = ptr[0];
        u8 g = ptr[1];
        u8 b = ptr[2];
        u8 a = ptr[3];

        colors.push_back({ r, g, b, a });
        i += sizeof(u32);
        ptr += sizeof(u32);
    }

    pal = SDL_CreatePalette(colors.size());
    SDL_SetPaletteColors(pal, colors.data(), 0, colors.size());

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
    SDL_SetPaletteColors(pal, default_pal_colors, 0, 32);
    return true;
}

void CTestState::Tick(f32 dT)
{
    SDL_RenderClear(theWindow->GetRenderer());
    SDL_SetRenderDrawColor(theWindow->GetRenderer(), 75, 75, 75, 255);
    CZIMGUI::Tick(dT);
    SDL_RenderTexture(theWindow->GetRenderer(), preview.texture, NULL, &preview.rect);
    SDL_RenderPresent(theWindow->GetRenderer());
}