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
    zdb::CTexture* ztexture;
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

    s32 pitch = 0;

    if (texture.m_format == SDL_PIXELFORMAT_RGBA32 || texture.m_format == SDL_PIXELFORMAT_RGBA8888)
    {
        pitch = texture.m_width * sizeof(u8) * 4;
    }
    else if (texture.m_format == SDL_PIXELFORMAT_RGB24)
    {
        pitch = texture.m_width * sizeof(u8) * 3;
    }
    else if (texture.m_format == SDL_PIXELFORMAT_RGBA5551 || texture.m_format == SDL_PIXELFORMAT_RGBA4444)
    {
        pitch = texture.m_width * sizeof(u8) * 2;
    }
    else if (texture.m_format == SDL_PIXELFORMAT_INDEX8)
    {
        pitch = texture.m_width * sizeof(u8);
    }
    
    preview.surface = SDL_CreateSurface(texture.m_width, texture.m_height, texture.m_format);
    
    if (!preview.surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
        return false;
    }

    u8* tex_ptr = (u8*)texture.m_buffer;

    for (u32 y = 0; y < texture.m_height; y++)
    {
        for (u32 x = 0; x < texture.m_width; x++)
        {
            SDL_Color col;

            if (texture.m_palettized)
            {
                col = pal->colors[*tex_ptr++];
            }
            else
            {
                if (texture.m_transparent)
                {
                    col = { tex_ptr[0], tex_ptr[1], tex_ptr[2], tex_ptr[3] };
                }
                else
                {
                    col = { tex_ptr[0], tex_ptr[1], tex_ptr[2], 255 };
                }
                
                tex_ptr += sizeof(u32);
            }
            
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

    if (texture.m_bilinear)
    {
        SDL_SetTextureScaleMode(preview.texture, SDL_SCALEMODE_LINEAR);
    }
    else
    {
        SDL_SetTextureScaleMode(preview.texture, SDL_SCALEMODE_NEAREST);
    }

    preview.surface = SDL_ConvertSurface(preview.surface, SDL_PIXELFORMAT_RGBA32);
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
        u8 r = 0;
        u8 g = 0;
        u8 b = 0;
        u8 a = 0;

        if (palette.m_format == 2)
        {
            a = ptr[0] & 0xF0;
            b = ptr[0] & 0x0F;
            g = ptr[1] & 0xF0;
            r = ptr[1] & 0x0F;
            
            i += sizeof(u16);
            ptr += sizeof(u16);
        }
        else
        {
            r = ptr[0];
            g = ptr[1];
            b = ptr[2];
            a = ptr[3];
            
            i += sizeof(u32);
            ptr += sizeof(u32);
        }
        
        colors.insert(colors.begin(), { r, g, b, a });
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
    CZIMGUI::Tick(dT);
    SDL_SetRenderDrawColor(theWindow->GetRenderer(), 15, 15, 15, 255);
    SDL_RenderTexture(theWindow->GetRenderer(), preview.texture, NULL, &preview.rect);
    SDL_RenderPresent(theWindow->GetRenderer());
}