#pragma once
#include <vector>
#include <list>

#include "gamez/zSystem/zsys.h"

namespace zdb
{
	enum _RenderPhase;

	class CModel;
	class CTexture;
	class CTexPalette;

	class CModelVector : public std::vector<CModel*> {};
	class CTexList : public std::vector<CTexture*> {};
	class CTexPalList : public std::vector<CTexPalette*> {};
}

namespace zdb
{
	class CAssetLib
	{
	public:
		char* RootName() const;
	private:
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

	class CAssetMgr
	{
	public:
		static std::list<CAssetLib*> m_assets;
	};
}