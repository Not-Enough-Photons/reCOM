#include <imgui/imgui.h>

#include "gamez/zSystem/zsys.h"

class CZIMGUI
{
public:
    CZIMGUI() = delete;
    
    static void Init();
    static void Shutdown();

    static bool Tick(f32 dT);

    static ImGuiIO m_io;
};