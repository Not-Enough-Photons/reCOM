#include "zimgui.h"

#include <SDL3/SDL_dialog.h>

#include "gamez/zArchive/zar.h"
#include "gamez/zUtil/zutil.h"
#include "gamez/zVideo/zvid.h"
#include "gamez/zVisual/zvis.h"
#include "SDL3/SDL_log.h"

zar::CZAR* current_archive = NULL;

char zar_input_path[256];
const char* zar_dir = "";

void ZARFileCallback(void* userdata, const char * const *filelist, int filter)
{
    if (filelist)
    {
        if (current_archive)
        {
            current_archive->Close();
            delete current_archive;
            current_archive = NULL;
        }
        
        zar_dir = *filelist;
        current_archive = new zar::CZAR();

        if (!current_archive->Open(zar_dir, 0, 0, 16))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open ZAR file!");
        }
        else
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ZAR file opened!");
        }
    }
    else
    {
        zar_dir = "";
    }
}

void DisplayKeys(zar::CKey* root, s32 depth)
{
    auto key_iterator = root->begin();

    if (key_iterator == root->end())
    {
        return;
    }

    u32 i = 0;
    
    while (key_iterator != root->end())
    {
        zar::CKey* key = *key_iterator;
        ImGui::PushID(depth * 1000 + i++);
        if (ImGui::TreeNode(key->GetName()))
        {
            ImGui::Text("Size: %u bytes\nOffset: %u bytes", key->GetSize(), key->GetOffset());
            if (ImGui::Button("Open"))
            {
                zdb::CMesh* mesh;
                u32* data = NULL;
                _word128* meshword = NULL;
                auto meshkey = current_archive->OpenKey(key);
                if (meshkey)
                {
                    if (current_archive->FetchLIP(meshkey, reinterpret_cast<void**>(meshword)))
                    {
                        u32 ofs = 0;

                        current_archive->Fetch(key->GetName(), &ofs);
                        current_archive->Fetch(key->GetName(), &mesh->m_mtx_count);

                        data = &meshword->u32[ofs];
                    }

                    current_archive->CloseKey(meshkey);
                }
                current_archive->CloseKey(key);
            }
            
            if (key->size() > 1)
            {
                DisplayKeys(key, depth + 1);
            }
            ImGui::TreePop();
        }
        ImGui::PopID();
        key_iterator++;
    }
}

bool CZIMGUI::Tick_ZARDisplay(f32 dT)
{
    if (ImGui::Begin("ZAR Editor"))
    {
        if (ImGui::Button("Open ZAR..."))
        {
            SDL_ShowOpenFileDialog(ZARFileCallback, NULL, theWindow->GetWindow(), NULL, 0, "D:/", false);
        }

        if (current_archive)
        {
            u32 i = 0;
            for (auto it = current_archive->m_root->begin(); it != current_archive->m_root->end(); ++it)
            {
                zar::CKey* key = *it;

                ImGui::PushID(i++);
                DisplayKeys(key, 0);
                ImGui::PopID();
            }
        }

        ImGui::End();
    }
    
    return true;
}
