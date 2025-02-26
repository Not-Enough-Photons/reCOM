#include "zanim.h"

bool zAnimWaitTick(_zanim_cmd_hdr* header, f32* dT)
{
    bool status = false;
    f32 timer = 0.0f;
    
    if ((header->data_type & 8) != 0)
    {
        if ((header->data_type & 4) == 0)
        {
            if ((header->data_type & 2) == 0)
            {
                timer = ZAnim.m_CurSeq->cmd_timer;
            }
            else
            {
                timer = ZAnim.m_CurSeq->seq_timer;
            }
        }
        else
        {
            timer = ZAnim.m_CurAnim->m_timer;
        }

        if ((f32)header->data_size < timer + *dT)
        {
            timer = (f32)header->data_size - timer;

            if (timer < 0.0f)
            {
                timer = 0.0f;
            }

            status = true;
            *dT -= timer;
        }
        else
        {
            *dT = 0.0f;
            status = false;
        }
    }
    
    // TODO: add fucked bitfield header if check or whatever
    
    return status;
}

bool zAnimWhileTick(_zanim_cmd_hdr* header, f32* dT)
{
    if (header->data_type == 0)
    {
        ZAnim.CmdNext(8);
        if (CZAnimExpression::ProcExpr(dT))
        {
            ZAnim.CmdSet(header->data_size);
        }
    }

    return true;
}

_zanim_cmd_hdr* CZAnimExpression::NewCmd(const char* operation)
{
    if (operation)
    {
        
    }

    return NULL;
}