#include "zimgui.h"

#include "gamez/zSound/zsnd.h"

bool CZIMGUI::Tick_SoundDisplay(f32 dT)
{
    if (ImGui::Begin("Sounds"))
    {
        if (ImGui::Button("Load"))
        {
            CSnd::Init();
        }
        
        s32 id = 0;
        for (auto it = CSnd::m_vagArchive.m_stable->begin(); it != CSnd::m_vagArchive.m_stable->end(); ++it)
        {
            id++;

            ImGui::PushID(id);
            if (ImGui::TreeNode(*it))
            {
                if (ImGui::Button("Play"))
                {
                    if (SDL_strstr(*it, ".wav") || SDL_strstr(*it, ".WAV"))
                    {
                        CSnd::LoadWAV(*it);
                    }
                    
                    if (SDL_strstr(*it, ".vag") || SDL_strstr(*it, ".VAG"))
                    {
                        CSnd::LoadVAG(*it);
                    }

                    if (SDL_strstr(*it, ".vpk") || SDL_strstr(*it, ".VPK"))
                    {
                        CSnd::LoadVPK(*it);
                    }
                }
                
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
        
        ImGui::End();
    }

    return true;
}
