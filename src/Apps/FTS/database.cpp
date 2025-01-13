#include "gamez/zNode/znode.h"

extern zdb::CWorld* theWorld = NULL;

bool LoadWorld(const char* name)
{
	zdb::CNodeUniverse* universe = zdb::NodeUniverse;

	if (universe == NULL)
	{
		universe = new zdb::CNodeUniverse();
		universe->m_locked = false;
	}

	zdb::NodeUniverse = universe;
	zdb::NodeUniverse->m_locked = false;
	zdb::CSaveLoad sload = zdb::CSaveLoad();

	theWorld = sload.Load(name);

	if (theWorld == NULL)
	{
		zdb::NodeUniverse->m_locked = true;
		// delete sload;
	}
	else
	{

	}

	return false;
}

bool UnloadTheWorld()
{
	return false;
}

bool testLoad()
{
	return false;
}

bool testUnload()
{
	return false;
}