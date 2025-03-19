#include "zseal.h"

f32 CZKit::GetCurZoom() const
{
    f32 zoom = 1.0f;
    CZFTSWeapon* item = m_item[m_selected_item];

    if (item)
    {
        f32 cur_zoom = m_body->m_zoomval;

        if (cur_zoom < static_cast<f32>(item->m_thirdZoomLevel))
        {
            zoom = item->GetZoomRange(cur_zoom);
        }
    }

    return zoom;
}