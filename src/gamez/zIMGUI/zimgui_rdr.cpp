#include "zimgui.h"

#include <SDL3/SDL_dialog.h>

#include "gamez/zArchive/zar.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zReader/zrdr_local.h"
#include "gamez/zVideo/zvid.h"

zar::CZAR rdrArchive;
const char* rdr_dir;

void FileCallback(void* userdata, const char * const *filelist, int filter)
{
    if (filelist)
    {
        rdrArchive.Close();
        rdr_dir = *filelist;
        rdrArchive = *CRdrArchive::AddArchive(rdr_dir, NULL);
        CRdrArchive::OpenAll();
    }
    else
    {
        rdr_dir = "";
    }
}

bool CZIMGUI::Tick_ReaderDisplay(f32 dT)
{
    if (ImGui::Begin("zReader"))
    {
        if (ImGui::Button("Load"))
        {
            SDL_ShowOpenFileDialog(FileCallback, NULL, theWindow->GetWindow(), NULL, 0, "D:/", false);
        }
        
        s32 id = 0;
        
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
                    sprintf_s(path, 256, "%s/%s", "data/common/zrdr", *it);
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
