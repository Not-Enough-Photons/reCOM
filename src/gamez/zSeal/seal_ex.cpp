#include "zseal.h"

void CSealEx::OnWeaponHit(CNode* node, zdb::IntersectStruct* intersection, CZProjectile* projectile)
{
    m_seal->OnWeaponHit(intersection, projectile);
}
