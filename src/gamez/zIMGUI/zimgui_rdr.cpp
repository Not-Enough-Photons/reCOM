#include "zimgui.h"

#include "gamez/zArchive/zar.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zReader/zrdr_local.h"

zar::CZAR rdrArchive;

bool CZIMGUI::Tick_ReaderDisplay(f32 dT)
{
    if (ImGui::Begin("zReader"))
    {
        if (ImGui::Button("Load"))
        {
            rdrArchive = *CRdrArchive::AddArchive("READERC.ZAR", "D:/RUN");
            CRdrArchive::OpenAll();
        }
        
        s32 id = 0;

        //for (auto it = archive->m_stable->begin(); it != archive->m_stable->end(); ++it)
        //{
        //    char* str = *it;
        //    CRdrFile* reader = zrdr_read(str, NULL, 0);
        //    FILE* file = fopen(str, "w");
        //    _OutputASCII(file, reader, 0);
        //    fclose(file);
        //}
        
        for (auto it = rdrArchive.m_stable->begin(); it != rdrArchive.m_stable->end(); ++it)
        {
            id++;

            ImGui::PushID(id);
            if (ImGui::TreeNode(*it))
            {
                if (ImGui::Button("Dump"))
                {
                    CRdrFile* reader = zrdr_read(*it, NULL, 0);
                    char path[256];
                    sprintf_s(path, 256, "%s/%s", "data/common/zrdr/", *it);
                    FILE* file = fopen(path, "w");
                    _OutputASCII(file, reader, 0);
                    fclose(file);
                }
                
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
        
        ImGui::End();
    }

    return true;
}
