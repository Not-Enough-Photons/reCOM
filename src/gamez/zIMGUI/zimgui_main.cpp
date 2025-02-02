#include "zimgui.h"

#include <SDL3/SDL.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlrenderer3.h>

#include "gamez/zSound/zsnd.h"
#include "gamez/zTexture/ztex.h"
#include "gamez/zVideo/zvid.h"

ImGuiIO CZIMGUI::m_io;

zar::CZAR texarchive;
zar::CZAR palarchive;

bool LoadTexture(zdb::CTexture texture);
bool LoadPalette(zdb::CTexPalette pal);

void LoadZAR();

const char* dir;

void FileDialogCallback_ZAR(void* userdata, const char * const *filelist, int filter)
{
    if (filelist)
    {
        texarchive.Close();
        dir = *filelist;
        texarchive.Open(dir, 0, 0, 16);
    }
    else
    {
        dir = "";
    }
}

void FileDialogCallback_PAL(void* userdata, const char * const *filelist, int filter)
{
    if (filelist)
    {
        palarchive.Close();
        dir = *filelist;
        palarchive.Open(dir, 0, 0, 16);
    }
    else
    {
        dir = "";
    }
}

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

    if (ImGui::Begin("Texture"))
    {
        if (ImGui::Button("Open Texture ZAR"))
        {
            SDL_ShowOpenFileDialog(FileDialogCallback_ZAR, NULL, theWindow->GetWindow(), NULL, 0, "D:/", false);
        }
    
        if (texarchive.m_stable->size() <= 0)
        {
            ImGui::End();
            ImGui::Render();
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), theWindow->GetRenderer());
            return false;
        }
    
        if (ImGui::CollapsingHeader("Textures"))
        {
            s32 id = 0;
            for (auto it = texarchive.m_stable->begin(); it != texarchive.m_stable->end(); ++it)
            {
                char* key = *it;

                ImGui::PushID(id++);
                if (ImGui::TreeNode(key))
                {
                    if (ImGui::Button("Load"))
                    {
                        auto root = texarchive.OpenKey("textures");
                        auto texkey = texarchive.OpenKey(*it);
                        zdb::CTexture tex;
                        tex.Read(texarchive);
                        LoadTexture(tex);
                        texarchive.CloseKey(texkey);
                        texarchive.CloseKey(root);
                    }
                    ImGui::TreePop();
                }
                ImGui::PopID();
            }
        }
        
        ImGui::End();
    }

    if (ImGui::Begin("Palette"))
    {
        if (ImGui::Button("Open Palette ZAR"))
        {
            SDL_ShowOpenFileDialog(FileDialogCallback_PAL, NULL, theWindow->GetWindow(), NULL, 0, "D:/", false);
        }
    
        if (palarchive.m_stable->size() <= 0)
        {
            ImGui::End();
            ImGui::Render();
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), theWindow->GetRenderer());
            return false;
        }
    
        if (ImGui::CollapsingHeader("Palettes"))
        {
            s32 id = 0;
            for (auto it = palarchive.m_stable->begin(); it != palarchive.m_stable->end(); ++it)
            {
                char* key = *it;

                ImGui::PushID(id++);
                if (ImGui::TreeNode(key))
                {
                    if (ImGui::Button("Apply"))
                    {
                        auto root = palarchive.OpenKey("palettes");
                        auto palkey = palarchive.OpenKey(*it);
                        zdb::CTexPalette pal;
                        pal.Read(palarchive);
                        LoadPalette(pal);
                        palarchive.CloseKey(palkey);
                        palarchive.CloseKey(root);
                    }
                    ImGui::TreePop();
                }
                ImGui::PopID();
            }
        }
        
        ImGui::End();
    }

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

