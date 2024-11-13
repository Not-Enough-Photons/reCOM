#include "fts.h"
#include "entity/seal/seal.h"

void CZSealBody::AttemptBombDefuse() const
{
	CZBombState::m_FutureBombState = 4;

	if (theMission.netGame != NULL && theMission.netGame.field_0x93 != 0)
	{
		theNetwork.zNetRequestObjectPrivateOwnership(theMission.netGame.field55_0x70);
	}
}