#include "zassetlib.h"

void HookupLib(zdb::CAssetLib lib)
{
    zdb::CGSTexBuffer texbuf;

    for (auto it = lib.m_palettes.begin(); it != lib.m_palettes.end(); ++it)
    {
        texbuf.m_dyntex_list.Add(*it, true);
        texbuf.m_chainp = NULL;
    }

    for (auto it = lib.m_textures.begin(); it != lib.m_textures.end(); ++it)
    {
        texbuf.m_dyntex_list.Add(*it, true);
        texbuf.m_chainp = NULL;
    }
    
    texbuf.Hookup(NULL);
}