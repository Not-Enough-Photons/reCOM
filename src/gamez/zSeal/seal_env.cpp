#include "zseal.h"

void CZSealBody::OnWeaponHit(zdb::IntersectStruct* intersection, CZProjectile* projectile)
{
    
}

void CZSealBody::SetWallHit(zdb::IntersectStruct* wallhit, CPnt3D* first, CPnt3D* second)
{
    if (!wallhit)
    {
        m_fwdhit->m_node = NULL;
    }
    else
    {
        memcpy(m_fwdhit, wallhit, sizeof(zdb::IntersectStruct));
        m_fwdhit->m_hit0 = *first;
        m_fwdhit->m_hit1 = *second;
    }
}