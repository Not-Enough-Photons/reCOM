#include "zvalve.h"

std::list<CValve*> CValve::m_list;

CValve* CValvePool::Acquire(const char* name, VALVE_TYPE type)
{
    if (!empty() && name && type == VALVE_TYPE::TEMP)
    {
        size_t length = strlen(name);
    }
}