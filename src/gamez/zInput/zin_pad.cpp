#include "zinput.h"
#include "SDL3/SDL_gamepad.h"

CPad::CPad(u32 port, u32 slot)
{
    m_port = port;
    m_slot = slot;

    if (port == 0 || port == 1)
    {
        m_open = SDL_OpenGamepad(port) != 0;
    }
}

void CPad::SetButtonState(PAD_BUTTON button, KEY_STATE state)
{
    m_state[(u8)button] = state;
    m_click[(u8)button] = -3;
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