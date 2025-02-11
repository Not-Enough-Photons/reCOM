#include "zimgui.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlrenderer3.h>

#include "gamez/zVideo/zvid.h"

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

    // Tick_TextureDisplay(dT);
    // Tick_SoundDisplay(dT);
    // Tick_ReaderDisplay(dT);
    Tick_ZARDisplay(dT);
    
    ImGui::Render();
    
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), theWindow->GetRenderer());

    return true;
}

void CZIMGUI::Shutdown()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}