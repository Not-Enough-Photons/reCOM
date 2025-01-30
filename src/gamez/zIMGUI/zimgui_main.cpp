#include "zimgui.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlrenderer3.h>

#include "gamez/zSound/zsnd.h"
#include "gamez/zVideo/zvid.h"

ImGuiIO CZIMGUI::m_io;

void CZIMGUI::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_io = ImGui::GetIO();

    m_io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(theWindow->GetWindow(), theWindow->GetRenderer());
    ImGui_ImplSDLRenderer3_Init(theWindow->GetRenderer());
}

bool CZIMGUI::Tick(f32 dT)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        ImGui_ImplSDL3_ProcessEvent(&e);
    }
    
    ImGui_ImplSDL3_NewFrame();
    ImGui_ImplSDLRenderer3_NewFrame();
    
    ImGui::NewFrame();
    
    if (ImGui::CollapsingHeader("Sounds"))
    {
        s32 id = 0;
        for (auto it = CSnd::m_vagArchive.m_stable->begin(); it != CSnd::m_vagArchive.m_stable->end(); ++it)
        {
            char* key = *it;

            ImGui::PushID(id++);
            if (ImGui::TreeNode(key))
            {
                if (ImGui::Button("Play"))
                {
                    CSnd::LoadVAG(key);
                }
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
    }

    ImGui::Render();
    
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), theWindow->GetRenderer());

    SDL_RenderPresent(theWindow->GetRenderer());
    
    return true;
}

void CZIMGUI::Shutdown()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

