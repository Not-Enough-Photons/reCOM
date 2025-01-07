#include "zfts.h"

CZSealBody* ftsPlayer = NULL;

CZSealBody* ftsGetPlayer()
{
	return ftsPlayer;
}

void ftsSetPlayer(CZSealBody* player)
{
	ftsPlayer = player;
}