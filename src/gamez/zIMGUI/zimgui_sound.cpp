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
                    CSnd::LoadVAG(*it);
                }
                
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
        
        ImGui::End();
    }

    return true;
}
