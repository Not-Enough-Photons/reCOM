﻿#include "ztwod.h"
#include "gamez/zAssetLib/zassetlib.h"

C2DMessage_Q::C2DMessage_Q()
{
    m_scale = 1.0f;
    m_maxsize = 3;
    m_top = 100;
    m_left = 20;
    m_maxtrans = 100.0f;
    m_transstep = 3.0f;
    m_time = 0;
    m_green = 100;
    m_blue = 100;
    m_red = 100;
    m_lowestbottom = m_top + 20;
    m_spacing = 20;
    m_centered = false;
    m_TtySpeed = 100000.0f;
    m_moveTime = 0.0f;
    m_cur_top = 0;
    m_target_top = 0.0f;
    m_bEnabled = true;
}

void C2DMessage_Q::Init(C2DFont* font, CRdrFile* reader)
{
    m_font = font;

    if (reader)
    {
        auto color = zrdr_findtag(reader, "color");

        if (color)
        {
            zrdr_findint(color, "red", &m_red);
            zrdr_findint(color, "green", &m_green);
            zrdr_findint(color, "blue", &m_blue);
        }

        zrdr_findreal(reader, "scale", &m_scale);
        zrdr_findreal(reader, "fadetime", &m_transstep);
        zrdr_findint(reader, "left", &m_left);
        zrdr_findint(reader, "bottom", &m_top);
        zrdr_findint(reader, "maxsize", &m_maxsize);
        zrdr_findint(reader, "spacing", &m_spacing);

        if (zrdr_findtag(reader, "centered"))
        {
            m_centered = true;
        }

        if (zrdr_findtag(reader, "descends"))
        {
            m_descends = true;
        }
        else
        {
            m_descends = false;
        }

        zrdr_findreal(reader, "maxlength", &m_maxlength, 1);

        char* background = zrdr_findstring(reader, "background");

        if (!background)
        {
            m_background1.Reset();
            m_background2.Reset();
        }
        else
        {
            m_YMargin = 0;
            m_XMargin = 0;

            zrdr_findint(reader, "XMargin", &m_XMargin);
            zrdr_findint(reader, "YMargin", &m_YMargin);

            zdb::CTexHandle* handle = zdb::CAssetMgr::m_assets.GetTexHandle(background);

            if (!handle)
            {
                m_background1.Reset();
                m_background2.Reset();
            }
            else
            {
                m_background1.Load(0.0f, 0.0f, 0.0f, 0.0f, handle);
                m_background1.SetUV(1.0f, 1.0f, 0.05f, 0.0f);
                m_background1.TickFade();
                m_background1.SetTrans(64);

                m_background2.Load(0.0f, 0.0f, 0.0f, 0.0f, handle);
                m_background2.SetUV(0.05f, 0.0f, 1.0f, 1.0f);
                m_background2.TickFade();
                m_background2.SetTrans(64);
            }

            m_target_top = -m_YMargin;
            m_moveTime = 1.0f;
        }

        zrdr_findreal(reader, "TtySpeed", &m_TtySpeed, 1);
    }
}

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