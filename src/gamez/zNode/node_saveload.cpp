#include "znode.h"

#include "gamez/zArchive/zar.h"
#include "gamez/zFTS/zfts.h"
#include "gamez/zSystem/zsys.h"

namespace zdb
{
	CSaveLoad::CSaveLoad()
	{
		m_world = NULL;
		m_zfile = zar::CZAR();
		m_zed_filename[0] = '\0';
		m_version = 0;
	}

	CWorld* CSaveLoad::Load(const char* name)
	{
		zdb::CWorld* world = NULL;

		FilterMissionFolder(name, "/run", name, m_zed_filename);
		strcat(m_zed_filename, "/");
		strcat(m_zed_filename, name);
		strcat(m_zed_filename, ".zed");

		u32 version = zdb::CWorld::GetVersion();

		if (!m_zfile.Open(m_zed_filename, version, 1, 16))
		{
			m_zfile.Close();
			world = NULL;
		}
		else
		{
			world = new zdb::CWorld();

			m_world = world;
			m_world->Init();
		}

		return world;
	}

	CNode* CNode::CreateInstance(CSaveLoad& saver)
	{
		char* modelName;
		tag_NODE_PARAMS nodeParams;
		u32 regionMask;

		// Is there no root?
		if (CWorld::m_world == NULL)
		{
			return NULL;
		}
		else
		{
			// InitNodeParams(NULL);

			if (&saver.m_zfile == NULL)
			{
				return NULL;
			}

			saver.m_zfile.Fetch("model_name", &modelName);
			saver.m_zfile.Fetch("nparams", &nodeParams, sizeof(tag_NODE_PARAMS));
			saver.m_zfile.Fetch("regionmask", &regionMask, sizeof(u32));
		}
	}
}