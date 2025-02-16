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
        bool success = true;
        
        m_world = world;
        
        if ((type & TYPE_TEXTURES) != 0)
        {
            std::string temp(library->RootName());
            temp.assign(temp.substr(0, 4));
    
            sprintf_s(m_zed_filename, 256, "%s%s/%s%s.zed", gamez_GamePath, library->m_name, temp.c_str(), "_txr");

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

        if ((type & TYPE_PALETTES) != 0)
        {
            std::string temp(library->RootName());
            temp.assign(temp.substr(0, 4));
            
            sprintf_s(m_zed_filename, 256, "%s%s/%s%s.zed", gamez_GamePath, library->m_name, temp.c_str(), "_pal");

            if (!m_zfile.Open(m_zed_filename, CWorld::GetVersion(), 1, 16))
            {
                m_zfile.Close();
                success = false;
            }
            else
            {
                success = LoadPalettes_PS2(library);
                m_zfile.Close();
            }
        }

        if ((type & TYPE_MODELS) != 0)
        {
            std::string temp(library->RootName());
            temp.assign(temp.substr(0, 4));
    
            sprintf_s(m_zed_filename, 256, "%s%s/%s%s.zed", gamez_GamePath, library->m_name, temp.c_str(), "_mdl");

            if (!m_zfile.Open(m_zed_filename, CWorld::GetVersion(), 1, 16))
            {
                m_zfile.Close();
                success = false;
            }
            else
            {
                if (auto key = m_zfile.OpenKey("models"))
                {
                    auto it = key->begin();
                    while (it != key->end())
                    {
                        if (auto model_key = m_zfile.OpenKey(*it))
                        {
                            CModel* model = CModel::Create(*this, NULL);
                            library->AddModel(model);
                            m_zfile.CloseKey(model_key);
                        }

                        ++it;
                    }

                    m_zfile.CloseKey(key);
                }
                
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
