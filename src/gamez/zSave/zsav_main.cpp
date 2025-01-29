#include "zsave.h"

#include "gamez/zAssetLib/zassetlib.h"
#include "gamez/zRender/zrender.h"

namespace zdb
{
    CSaveLoad::CSaveLoad()
    {
        m_world = NULL;
        m_zfile = zar::CZAR();
        m_zed_filename[0] = '\0';
        m_version = 0;
    }

    bool CSaveLoad::LoadAssetLib(CWorld* world, CAssetLib* library, u32 type)
    {
        return LoadAssetLib_PS2(world, library, type);
    }

    bool CSaveLoad::LoadAssetLib_PS2(CWorld* world, CAssetLib* library, u32 type)
    {
        char rootnamebuf[4];
        bool success = true;
        
        m_world = world;

        if ((type & TYPE_TEXTURES) == 0)
        {
            char* rootname = library->RootName();
            strcpy_s(rootnamebuf, 4, rootname);

            if (strlen(rootnamebuf) < 4)
            {
                // variable = 0?
            }

            sprintf_s(m_zed_filename, "D:/run/%s/%s%s.zed", library->m_name, rootnamebuf, "_txr");

            if (!m_zfile.Open(m_zed_filename, CWorld::GetVersion(), 1, 16))
            {
                m_zfile.Close();
                success = false;
            }
            else
            {
                success = LoadTextures_PS2(library);
                m_zfile.Close();
            }
        }

        return success;
    }
    
    bool CSaveLoad::LoadTextures_PS2(CAssetLib* library)
    {
        CTexture* texture = NULL;
        s32 renderphase;

        // TODO: fix renderphase enum
        if (m_zfile.Fetch("renderphase", &renderphase))
        {
            
        }

        zar::CKey* key = m_zfile.OpenKey("textures");

        if (key)
        {
            auto it = key->begin();

            while (it != key->end())
            {
                zar::CKey* texturekey = m_zfile.OpenKey(*it);

                if (texturekey)
                {
                    char* name = texturekey->GetName();
                    CTexHandle* handle = CAssetMgr::m_assets.GetTexHandle(name);

                    if (handle && library->AddTexture(name))
                    {
                        texture = new CTexture(name);
                        texture->Read(*this);
                        library->AddTexture(texture);
                    }

                    m_zfile.CloseKey(texturekey);
                }
                
                ++it;
            }

            m_zfile.CloseKey(key);
        }

        library->m_texture_buffer = m_zfile.ReleaseDataBuffer();
        return true;
    }
}
