#include "zseal.h"

#include "gamez/zCharacter/zchar.h"

void SealInitCharacterDynamics()
{
    CRdrFile* dynamics = zrdr_read("dynamics.rdr");
    if (!theCharacterDynamics.m_loaded && dynamics)
    {
        theCharacterDynamics.Load(dynamics);
        zrdr_free(dynamics);
    }

    CZSealBody::InitLookAnims();
}