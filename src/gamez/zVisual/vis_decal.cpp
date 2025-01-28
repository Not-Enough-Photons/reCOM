#include "zvis.h"

namespace zdb
{
    void CVisual::ApplyDecal(CDecal* decal)
    {
        CDecal* applied = NULL;
        auto it = m_decals.begin();

        while (it != m_decals.end())
        {
            if (!(*it))
            {
                return;
            }

            if ((*it) == decal)
            {
                break;
            }

            ++it;
            applied = *it;
        }

        if (applied == NULL)
        {
            m_decals[m_decal_idx] = *it;
        }
        else
        {
            applied = *it;
        }

        *it = NULL;
    }

}
