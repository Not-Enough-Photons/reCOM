#include "node_main.h"
#include "node_world.h"

namespace zdb
{
	void CWorld::ReserveChildren(int count)
	{
		children.reserve(count + expandSize);
	}
}