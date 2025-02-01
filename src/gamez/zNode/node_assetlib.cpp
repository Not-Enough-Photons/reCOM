#include "znode.h"

#include "gamez/zAssetLib/zassetlib.h"
#include "gamez/zSave/zsave.h"

namespace zdb
{
	CAssetList CAssetMgr::m_assets;

	CAssetList g_assetsRecycle;

	CModel* CAssetList::GetModel(const char* name)
	{
		CModel* model = NULL;

		if (m_cache_model == NULL || name == NULL || strcmp(m_cache_model->m_name, name) != 0)
		{
			auto it = begin();

			while (it != end())
			{
				CAssetLib* lib = *it;
				model = lib->m_models.GetModel(name);

				if (model != NULL)
				{
					break;
				}
			}

			m_cache_model = model;
		}
		else
		{
			model = m_cache_model;
		}

		return model;
	}

	bool CAssetLib::IsNamed(const char* name) const
	{
		bool isnamed = false;

		if (strcmp(name, m_name) == 0)
		{
			isnamed = true;
		}
		else
		{
			size_t length = strlen(name);
			s32 i = length - 1;
			length = strlen(m_name);
			s32 j = length - 1;
			isnamed = true;

			// TODO:
			// clean this up
			do
			{
				for (; (-1 < i) && (name[i] == '/' || name[i] == '\\'); --i) {}
				for (; (-1 < j) && (m_name[j] == '/' || m_name[j] == '\\'); --j) {}

				if (i < 0 || j < 0)
				{
					if (i == j)
					{
						return isnamed;
					}

					isnamed = false;
				}
				else if (name[i] == m_name[j])
				{
					i--;
					j--;
				}
				else
				{
					isnamed = false;
				}
			}
			while (isnamed);
		}

		return isnamed;
	}
	
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

	CAssetLib* CAssetList::FindLib(const char* name)
	{
		CAssetLib* lib = NULL;
		
		if (!name)
		{
			return NULL;
		}
		else
		{
			auto it = begin();

			while (it != end())
			{
				if ((*it)->IsNamed(name))
				{
					lib = *it;
					break;
				}
				
				++it;
			}

			// If the library doesn't have a proper name -
			// search any subdirectories
			if (!lib)
			{
				it = begin();

				while (it != end())
				{
					CAssetLib* alib = *it;

					size_t length = strlen(alib->m_name);
					s32 idx = length - 1;
					char* libname = NULL;
					
					if (idx > -1)
					{
						do
						{
							char c = alib->m_name[idx];

							if (c == '/' || c == '\\')
							{
								libname = alib->m_name + idx + 1;
							}

							idx++;
						}
						while (idx > -1);
					}
					
					libname = alib->m_name + idx + 1;

					if (strcmp(libname, name) == 0)
					{
						return *it;
					}
					
					++it;
				}
			}
		}

		return lib;
	}
	
	CAssetLib* CAssetMgr::GetLoadedLibRef(const char* name)
	{
		CAssetLib* lib = m_assets.FindLib(name);

		// Check recycle asset lib container
		// Promotes efficient memory usage without allocating/deallocating
		if (!lib)
		{
			lib = g_assetsRecycle.FindLib(name);

			// Still nothing in the recycle bin
			// Empty the whole thing
			if (!lib)
			{
				for (auto it = g_assetsRecycle.begin(); it != g_assetsRecycle.end(); ++it)
				{
					delete *it;
				}

				g_assetsRecycle.erase(g_assetsRecycle.begin(), g_assetsRecycle.end());

				CSaveLoad sload;
				CAssetLib* assetlib = new CAssetLib(name);
			}
			else
			{
				// Library found, insert library into our asset list
				lib->m_iRefCount++;
				m_assets.insert(m_assets.begin(), lib);
			}
		}
		else
		{
			lib->m_iRefCount++;
		}

		for (auto it = g_assetsRecycle.begin(); it != g_assetsRecycle.end(); ++it)
		{
			if (*it)
			{
				delete *it;
			}

			*it = NULL;
		}

		g_assetsRecycle.erase(g_assetsRecycle.begin(), g_assetsRecycle.end());
		
		return lib;
	}

}
