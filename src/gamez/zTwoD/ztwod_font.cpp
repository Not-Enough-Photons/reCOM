#include "ztwod.h"
#include "gamez/zAssetLib/zassetlib.h"

C2DFont::C2DFont()
{
    m_pTexHandle = NULL;
    m_pGlowTexHandle = NULL;
    m_displaytop = 0;
    m_displaybottom = 0;
    m_opacity = 1.0f;
    m_scale_factor = 1.0f;
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
    s32 length = 0;

    if (charoffsets)
    {
        length = charoffsets->array->integer - 1;
    }
    else
    {
        length = 0;
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
