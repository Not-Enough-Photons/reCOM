#include "zvalve.h"

std::list<CValve*> CValve::m_list;

CValve* CValvePool::Acquire(const char* name, VALVE_TYPE type)
{
    CValve* valve = NULL;
    char* vname = NULL;
    
    if (m_has_name && name && type == VALVE_TYPE::VTYPE_TEMP)
    {
        size_t length = strlen(name);
        char* dest = m_pool_name;

        if (length + 1 <= m_pool_length - (s32)(dest - m_max_char_len))
        {
            m_pool_name = dest + length + 1;
            strcpy(dest, name);
            vname = dest;
        }
    }

    if (empty())
    {
        valve = new CValve(name, 0, type);

        if (vname)
        {
            valve->AssignName(vname);
        }
    }
    else
    {
        // Valve already exists in the pool.
        // Get the first valve and assign it a name.
        valve = front();

        // No name assigned from the pool?
        if (!vname)
        {
            // Use what we defined.
            // valve->SetName(name);
        }
        else
        {
            // A name was assigned from the pool
            // Use it.
            valve->AssignName(vname);
            valve->m_type = (u32)type;
        }
    }

    // Valve successfully retrieved from pool?
    if (valve)
    {
        VALVE_STATE vtype = VALVE_STATE::VSTATE_DORMANT;

        if (valve->m_value != 0)
        {
            vtype = VALVE_STATE::VSTATE_TEMPORARY;
        }

        valve->m_value = 0;

        if (vtype != VALVE_STATE::VSTATE_DORMANT)
        {
            // valve->MakeCallbacks(vtype);
        }
    }

    return valve;
}