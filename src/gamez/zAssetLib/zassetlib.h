#pragma once
#include <vector>
#include <list>

#include "gamez/zNode/znode.h"
#include "gamez/zTexture/ztex.h"
#include "gamez/zSystem/zsys.h"

enum class _RenderPhase;

namespace zdb
{
	class CModel;
	class CTexture;
	class CTexPalette;

	class CAssetLib;
}

extern void HookupLib(zdb::CAssetLib* lib);

namespace zdb
{
	class CAssetLib
	{
		friend class CAssetList;
	public:
		CAssetLib(const char* name);
		
		bool AddTexture(const char* name);
		bool AddTexture(zdb::CTexture* texture);
		CModel* AddModel(CModel* model);
		
		bool IsNamed(const char* name) const;
		char* RootName() const;
		
		char* m_name;

		CModelVector m_models;
		CTexList m_textures;
		CTexPalList m_palettes;

		bool m_autoload;
		bool m_locked;
		bool m_gearlib;

		_RenderPhase m_renderphase;

		void* m_texture_buffer;
		void* m_model_buffer;

		s32 m_iRefCount;
	};

	class CAssetList : public std::list<CAssetLib*>
	{
	public:
		CTexHandle* GetTexHandle(const char* name);
		CAssetLib* FindLib(const char* name);
		CModel* GetModel(const char* name);
	private:
		CModel* m_cache_model;
	};

	class CAssetMgr
	{
	public:
		static CAssetLib* GetLoadedLibRef(const char* name);
		
		static CAssetList m_assets;
	};

	class CRefList : public std::list<CAssetLib*> {};
}