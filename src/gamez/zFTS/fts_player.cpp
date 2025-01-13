#include "zfts.h"

bool doSquirm = false;
CZSealBody* ftsPlayer = NULL;

CZSealBody* ftsGetPlayer()
{
	return ftsPlayer;
}

void ftsSetPlayer(CZSealBody* player)
{
	ftsPlayer = player;
}

bool ftsGetSquirm()
{
	return doSquirm;
}

void ftsSetSquirm(bool squirm)
{
	doSquirm = squirm;
}