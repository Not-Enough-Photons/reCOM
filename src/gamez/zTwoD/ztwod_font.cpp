﻿#include "ztwod.h"
#include "gamez/zAssetLib/zassetlib.h"
#include "gamez/zVideo/zvid.h"

C2DFont::C2DFont()
{
    m_pTexHandle = NULL;
    m_pGlowTexHandle = NULL;
    m_displaytop = 0;
    m_displaybottom = 0;
    m_opacity = 1.0f;
    m_scale_factor = 1.0f;
}

u32 C2DFont::GetIndex(char character)
{
    u32 index = 0;

    while (true)
    {
        if (m_charlist.size() <= index)
        {
            return -1;
        }

        if (character == m_charlist[index * 40]->m_char)
        {
            break;
        }

        index++;
    }

    return index;
}

// TODO: Finish this function for loading fonts from a reader file
void C2DFont::Load(CRdrFile* font, const char* name)
{
    s32 topy = 0;
    s32 boty = 0;
    s32 xspacing = 0;
    
    auto faces = zrdr_findtag(font, "faces");
    auto font_name = zrdr_findtag(faces, name);

    char* texture = zrdr_findstring(font_name, "texture");
    char* glowtexture = zrdr_findstring(font_name, "glowtexture");

    zrdr_findint(font_name, "topy", &topy, 1);
    zrdr_findint(font_name, "boty", &boty, 1);
    zrdr_findint(font_name, "xspacing", &xspacing, 1);
    zrdr_findreal(font_name, "opacity", &m_opacity, 1);

    if (!zrdr_findtag(font_name, "scale"))
    {
        m_scale_factor = 1.0f;
    }
    else
    {
        zrdr_findreal(font_name, "scale", &m_scale_factor, 1);
    }

    if (texture)
    {
        m_pTexHandle = zdb::CAssetMgr::m_assets.GetTexHandle(texture);
    }

    if (glowtexture)
    {
        m_pGlowTexHandle = zdb::CAssetMgr::m_assets.GetTexHandle(glowtexture);
    }

    auto charoffsets = zrdr_findtag(font_name, "charoffsets");
    u32 i = 0;
    s32 length = 0;
    s32 node_length = 0;

    if (!charoffsets)
    {
        length = 0;
    }
    else if (charoffsets->type == ZRDR_ARRAY)
    {
        length = charoffsets->array->integer - 1;
    }
    else
    {
        length = 0;
    }

    if (length > 0)
    {
        do
        {
            _zrdr* node = NULL;
            char font_char = 0;
            
            node_length = 0;

            if (charoffsets->type == ZRDR_ARRAY)
            {
                node_length = charoffsets->array->integer - 1;
            }

            if (i < node_length)
            {
                node = &charoffsets->array[i + 1];
            }
            else
            {
                node = NULL;
            }

            if (node->type == ZRDR_ARRAY)
            {
                node_length = node->array->integer - 1;
            }
            else
            {
                node_length = 0;
            }

            if (node_length == 0)
            {
                node = NULL;
            }
            else
            {
                node = &node->array[1];
            }

            if (node->type == ZRDR_STRING)
            {
                font_char = *node->string;
            }
            else if (node->type == ZRDR_INTEGER)
            {
                font_char = (char)node->integer;
            }

            node_length = 0;

            if (node->type == ZRDR_ARRAY)
            {
                node_length = node->array->integer - 1;
            }

            if (node_length < 2)
            {
                node = NULL;
            }
            else
            {
                node = &node->array[2];
            }

            node_length = 0;

            if (node->type == ZRDR_ARRAY)
            {
                node_length = node->array->integer - 1;
            }

            if (node_length < 3)
            {
                node = NULL;
            }
            else
            {
                node = &node->array[3];
            }

            u32 char_idx = -1;
            for (char_idx = 0; char_idx < m_charlist.size(); char_idx++)
            {
                if (font_char == m_charlist[char_idx]->m_char)
                {
                    char_idx = -1;
                    break;
                }
            }

            if (char_idx == -1)
            {
                if (node->type == ZRDR_ARRAY)
                {
                    node_length = node->array->integer - 1;
                }

                if (node_length == 0)
                {
                    node = NULL;
                }
                else
                {
                    node = &node->array[1];
                }

                u32 value = 0;
                
                if (node->type == ZRDR_INTEGER)
                {
                    value = node->integer;
                }
                else if (node->type == ZRDR_REAL)
                {
                    value = static_cast<s32>(node->real);
                }
                else
                {
                    value = 0;
                }

                node_length = 0;

                if (m_pTexHandle)
                {
                    node_length = m_pTexHandle->m_texture->m_height;
                }

                node_length = 0;

                if (node->type == ZRDR_ARRAY)
                {
                    node_length = node->array->integer - 1;
                }

                if (node_length < 2)
                {
                    node = NULL;
                }
                else
                {
                    node = &node->array[2];
                }

                if (node->type == ZRDR_INTEGER)
                {
                    value = node->integer;
                }
                else if (node->type == ZRDR_REAL)
                {
                    value = static_cast<s32>(node->real);
                }
                else
                {
                    value = 0;
                }

                if (node->type == ZRDR_ARRAY)
                {
                    node_length = node->array->integer - 1;
                }
                else
                {
                    node_length = 0;
                }

                if (node_length == 0)
                {
                    node = NULL;
                }
                else
                {
                    node = &node->array[1];
                }

                if (node->type == ZRDR_INTEGER)
                {
                    value = node->integer;
                }
                else if (node->type == ZRDR_REAL)
                {
                    value = static_cast<s32>(node->real);
                }
                else
                {
                    value = 0;
                }

                if (node->type == ZRDR_ARRAY)
                {
                    node_length = node->array->integer - 1;
                }
                else
                {
                    node_length = node->array->integer - 1;
                }

                if (node_length < 2)
                {
                    node = NULL;
                }
                else
                {
                    node = &node->array[2];
                }

                if (node->type == ZRDR_INTEGER)
                {
                    value = node->integer;
                }
                else if (node->type == ZRDR_REAL)
                {
                    value = static_cast<s32>(node->real);
                }
                else
                {
                    value = 0;
                }

                C2DFontEntry entry;

                zrdr_findint(node, "baseline", &entry.m_baseline, 1);
                zrdr_findint(node, "lKerning", &entry.m_lKerning, 1);
                zrdr_findint(node, "rKerning", &entry.m_rKerning, 1);

                entry.m_offset = entry.m_baseline << 4;
                entry.m_width = entry.m_lKerning << 4;
                entry.m_displaywidth = entry.m_rKerning << 4;
                entry.m_char = font_char;
                
                m_charlist.insert(m_charlist.begin(), &entry);
            }

            i++;
        }
        while (i < length);
    }
}

void C2DTTFFont::Load(const char* path)
{
    m_ttf_font = TTF_OpenFont(path, 12.0f);
    
    if (!m_ttf_font)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
    }
}

C2DFontEntry* C2DFont::GetEntry(char character)
{
    C2DFontEntry* entry = NULL;

    for (u32 i = 0; i < m_charlist.size(); i++)
    {
        entry = m_charlist[i * 0x28];

        if (character == entry->m_char)
        {
            return entry;
        }
    }

    u32 i = 0;
    while (true)
    {
        if (i >= m_charlist.size())
        {
            return m_charlist[character % m_charlist.size() * 0x28];
        }

        entry = m_charlist[i * 0x28];

        if ((character % 0x26 + 'A') == entry->m_char)
        {
            break;
        }

        i++;
    }

    return entry;
}
