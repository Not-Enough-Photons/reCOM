#include "ztwod.h"

void C2DMessage_Q::ScrollUp()
{
    m_target_top = -m_YMargin;
    m_Distance = -m_YMargin - m_cur_top;
    m_moveTime = 0;
}

void C2DMessage_Q::SetBkgColor(f32 r, f32 g, f32 b)
{
    m_background1.SetColor(r, g, b);
    m_background2.SetColor(r, g, b);
}