#include "zimgui.h"

#include <SDL3/SDL_dialog.h>

#include "gamez/zArchive/zar.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zReader/zrdr_local.h"
#include "gamez/zVideo/zvid.h"

zar::CZAR rdrArchive;
const char* rdr_dir;
char path[256];
char input_path[256];

void FileCallback(void* userdata, const char * const *filelist, int filter)
{
    if (filelist)
    {
        // rdrArchive.Close();
        rdr_dir = *filelist;
        rdrArchive = *CRdrArchive::AddArchive(rdr_dir, NULL);
        CRdrArchive::OpenAll();

        for (auto it = rdrArchive.m_stable->begin(); it != rdrArchive.m_stable->end(); ++it)
        {
            CRdrFile* reader = zrdr_read(*it, NULL, 0);
            sprintf_s(path, 256, "%s/%s", input_path, *it);
            FILE* file = fopen(path, "w");
            _OutputASCII(file, reader, 0);
            fclose(file);
        }
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
        ImGui::InputText("Export Directory", input_path, 256);

        if (ImGui::Button("Dump"))
        {
            SDL_ShowOpenFileDialog(FileCallback, NULL, theWindow->GetWindow(), NULL, 0, "D:/", false);
        }
        
        ImGui::End();
    }

    return true;
}
