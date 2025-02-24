#include "hud.h"
#include "gamez/zSeal/zseal.h"

CZPauseTest::CZPauseTest()
{
    m_numselections = 0;
    m_curcolor = 0.0f;
    m_inc = 50.0f;
    m_font = NULL;
    m_oldmenustate = stateNone;
    m_selectsound = NULL;
    m_scrollupsound = NULL;
    m_scrolldownsound = NULL;
}

void CZPauseTest::OpenPauseMenu()
{
    CZSealBody* owner = CHUD::GetHUDOwner();
    CSealCtrl* control = NULL;
    CPad* player_pad = NULL;
    
    if (owner)
    {
        control = static_cast<CSealCtrl*>(owner->m_control);
    }

    control->StopRumbler();

    if (control->m_padid < 2)
    {
        player_pad = CInput::m_pads[control->m_padid];
    }

    player_pad->SetButtonState(PAD_BUTTON::PAD_START, KEY_DOWN);
    CSndInstance::PauseAllSounds();
    CSnd::PostTick(0.0f, NULL);

    On();

    theHUD->m_letterbox.AddLetterbox();

    if (theHUD->m_newmap.m_isFullScreen)
    {
        theHUD->m_newmap.SwitchToCompassMap();
    }

    theHUD->Off();

    m_oldmenustate = control->GetMenuState();
    control->SetMenuState(statePauseTestMenu);
}
