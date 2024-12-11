#include "znode.h"
#include "node_world.h"

namespace zdb
{
	CNode* CNode::CreateInstance(CSaveLoad& saver)
	{
		char* modelName;
		tag_NODE_PARAMS nodeParams;
		unsigned int regionMask;

		// Is there no root?
		if (CWorld::m_world == NULL)
		{
			return NULL;
		}
		else
		{
			InitNodeParams(NULL);

			if (&saver.m_zfile == NULL)
			{
				return NULL;
			}

			saver.m_zfile.Fetch("model_name", &modelName);
			saver.m_zfile.Fetch("nparams", &nodeParams, sizeof(tag_NODE_PARAMS));
			saver.m_zfile.Fetch("regionmask", &regionMask, sizeof(unsigned int));


		}
	}
}