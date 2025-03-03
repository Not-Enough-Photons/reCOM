#include "hud.h"

CHUD* theHUD;

s32 hudInit()
{
    CRdrIO* hud = zrdr_read("hud.rdr", "data/common");
    _zrdr* tacmap = zrdr_findtag(hud, "TacMap");
    _zrdr* polygons = zrdr_findtag(tacmap, "Polygons");
    _zrdr* lines = zrdr_findtag(tacmap, "Lines");

    if (polygons)
    {
        u32 i = 0;
        u32 children = 0;
        _zrdr* child = NULL;
        
        while (true)
        {
            if (children <= i)
            {
                break;
            }

            if (i < children)
            {
                child = &polygons->array[i];
            }
            else
            {
                child = NULL;
            }

            hudAddPolyType(child);
            i++;
        }
    }

    if (lines)
    {
        u32 i = 0;
        u32 children = 0;
        _zrdr* child = NULL;
        
        while (true)
        {
            if (children <= i)
            {
                break;
            }

            if (i < children)
            {
                child = &polygons->array[i];
            }
            else
            {
                child = NULL;
            }

            hudAddLineType(child);
            i++;
        }
    }

    return zrdr_free(hud);
}

CHUD::CHUD()
{

}

CZSealBody* CHUD::GetHUDOwner()
{
    return appCamera->m_entity;
}

void CHUD::Init(zdb::CWorld* world)
{

}