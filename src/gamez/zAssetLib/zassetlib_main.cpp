#include "zassetlib.h"

namespace zdb
{
	std::list<CAssetLib*> CAssetMgr::m_assets;

	char* CAssetLib::RootName() const
	{
		size_t length = strlen(m_name);

		for (int i = length - 1; i > -1; i--)
		{
			char c = m_name[i];

			if (c == '/' || c == '\\')
			{
				return m_name + i + 1;
			}
		}

		return m_name;
	}
}