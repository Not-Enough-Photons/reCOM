#include "zinput.h"

CPad::CPad(s32 port, s32 slot)
{
    if (port == 0 || port == 1)
    {

    }
}

void CPad::Flush()
{
    
}

void CPad::Tick(f32 delta)
{
    pad_dt = delta;
}

bool CPad::GetTwoButtons(PAD_BUTTON button1, PAD_BUTTON button2)
{
    bool falling = false;

    falling = m_state[(u32)button1] == KEY_DOWN;
    
    if (falling)
    {
        falling = m_state[(u32)button2] == KEY_FALLING;
    }

    return falling;
}

bool CPad::IsOpen()
{
    return m_open != 0;
}