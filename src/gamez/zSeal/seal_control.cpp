#include "zseal.h"

f32 CSealCtrl::m_bobbing1stperson_amplitude = 0.0f;
f32 CSealCtrl::m_bobbing1stperson_rate = 0.0f;
f32 CSealCtrl::m_crawl1stperson_amplitude = 0.0f;
f32 CSealCtrl::m_crawl1stperson_rate = 0.0f;

void CSealCtrl::StopRumbler()
{
    CPad* pad;
    
    if (m_padid < 2)
    {
        pad = CInput::m_pads[m_padid];
    }
    else
    {
        pad = NULL;
    }

    if (pad)
    {
        pad->m_ActData = 0;
        pad->m_IsAnalog = false;
    }

    m_highrumbletime = 0.0f;
    m_rumbletime = 0.0f;
    m_rumblestr = 0.0f;

    CInput::Flush();
    CZSealBody::StopAllHeartbeatSounds();
}

MENU_STATE CSealCtrl::GetMenuState()
{
    return m_menustate;
}

void CSealCtrl::SetMenuState(MENU_STATE state)
{
    if (state < stateLast)
    {
        m_menustate = state;
    }
}
