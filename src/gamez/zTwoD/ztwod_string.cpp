#include "ztwod.h"

C2DString::C2DString()
{
    m_string = (char*)zmalloc(17);
    m_stringlen_max = 16;
    m_numChars = 0;
    m_Ustring = (char*)zmalloc(17);
    *m_Ustring = '\0';
    m_Ustringlen_max = 16;
    m_numUChars = 0;
    m_font = NULL;
    m_scale = 1.0f;
    m_revnum = 0;
    m_color.x = 255.0f;
    m_color.y = 255.0f;
    m_color.z = 255.0f;
    m_color.w = 128.0f;
    m_firstCharPos = 0;
    m_elapsedTime = 0.0f;
}

void C2DString::AddCharacter(char character)
{
    m_numChars += 1;

    m_string = (char*)zrealloc(m_string, m_numChars + 1);

    if (m_numChars < 2)
    {
        *m_string = character;
        m_string[1] = '\0';
    }
    else
    {
        m_string[m_numChars - 1] = character;
        m_string[m_numChars] = '\0';
    }

    if (character != '\n')
    {
        s32 length = static_cast<s32>(m_length);
        C2DFontEntry* entry = m_font->GetEntry(character);

        if (entry)
        {
            if (entry->m_displaywidth == -1)
            {
                length = static_cast<s32>(length + m_scale * entry->m_width * m_font->m_scale_factor);
            }
            else
            {
                length += entry->m_displaywidth;
            }

            m_length += static_cast<f32>(length + entry->m_xspacing + entry->m_rKerning >> 4);
        }
    }
}