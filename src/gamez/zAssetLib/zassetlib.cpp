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

namespace zdb
{
    CTexHandle* CAssetList::GetTexHandle(const char* name)
    {
        CTexHandle* handle = NULL;
        
        auto it = begin();

        while (it != end())
        {
            handle = (*it)->m_textures.GetHandle(name);
            
            if (handle)
            {
                break;
            }

            ++it;
        }

        return handle;
    }
    
    CTexHandle* CTexList::Append(CTexture* texture, bool search)
    {
        CTexHandle* handle = NULL;

        if (search)
        {
            auto it = begin();
            
            while (it != end() && (*it)->m_texture != texture)
            {
                ++it;
            }
            
            if (it == end())
            {
                handle = NULL;
            }
            else
            {
                handle = *it;
            }
        }

        if (handle == NULL)
        {
            handle = CTexHandle::Create(texture);
            insert(begin(), handle);
        }

        return handle;
    }

    bool CAssetLib::AddTexture(const char* name)
    {
        CTexHandle* handle = NULL;
        
        if (m_locked)
        {
            return false;
        }

        if (!name)
        {
            return false;
        }

        auto it = CAssetMgr::m_assets.begin();

        while (it != CAssetMgr::m_assets.end())
        {
            handle = (*it)->m_textures.GetHandle(name);
            if (handle)
            {
                break;
            }
            
            ++it;
        }

        if (handle)
        {
            AddTexture(handle->m_texture);
            return true;
        }

        return false;
    }
    
    bool CAssetLib::AddTexture(zdb::CTexture* texture)
    {
        if (m_locked)
        {
            return false;
        }

        if (!texture)
        {
            return false;
        }

        auto it = CAssetMgr::m_assets.begin();

        while (it != CAssetMgr::m_assets.end())
        {
            auto handle = (*it)->m_textures.GetHandle(texture->m_name);

            if (handle)
            {
                break;
            }
        }

        if (!*it)
        {
            m_textures.Append(texture, true);
            texture->m_AssetLib = this;
        }
        
        return true;
    }
}