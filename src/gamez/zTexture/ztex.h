#pragma once
#include "gamez/zAssetLib/zAssetLib.h"
#include "gamez/zNode/znode.h"
#include "gamez/zSystem/zsys.h"

namespace zdb
{
	class CLoadImage;
	class CTexPalette;
	class CDynTexList;
	class CTexList;
	class CTexPalList;

	struct TEXTURE_PARAMS
	{
		u16 m_width;
		u16 m_height;
		u32 m_size;
		u32 m_gsaddr;
		u32 m_texelBitSize : 8;
		u32 m_selectQwc : 8;
		u32 m_pal_offset : 8;
		u32 m_transparent : 1;
		u32 m_palettized : 1;
		u32 m_is_mip_child : 1;
		u32 m_bumpmap : 1;
		u32 m_bilinear : 1;
		u32 m_transp_1bit : 1;
		u32 m_dynamic : 1;
		u32 m_context : 1;
	};

	struct PALETTE_PARAMS
	{
		u32 m_gsaddr;
		size_t m_size;
		u32 m_format : 8;
		bool m_combo_pal;
		bool m_dynamic;
		u32 m_unused : 6;
	};

	class CTexManager : public std::vector<CDynTexList*>
	{
	public:
		static CTexManager* m_texmanager;

		static void doAddBuffer(float param_1, float param_2, int param_3, const char* img);
	};

	class CTexture : public TEXTURE_PARAMS
 	{
	public:
		static void Init();
		CTexture* Read(CSaveLoad& saveload);
	private:
		CAssetLib* m_AssetLib;
		const char* m_name;
		void* m_buffer;
		CTexPalette* m_palette;
		long m_gifSelect;
		long m_vuSelect;
		u16 m_format;
		u16 m_palID;
		u16 m_htex_count;
		u16 m_gsWords;
		u64 m_dmaRef;
		u64 m_dmaRefVu;
		// GL_TEXTURE* gsTex0;
		// GL_MIP_TEXTURE* m_MIP1;
		// GL_MIP_TEXTURE* m_MIP2;
		std::vector<CTexture*> m_reverse_miplist;
		CLoadImage* m_loadimage;
	};

	class CTexList : public std::vector<CTexture*> {};

	class CTexPalList : public std::vector<CTexPalette*> {};

	class CDynTexList
	{
	public:
		void Add(CTexPalette* palette, bool check);
		void Add(CTexHandle* handle, bool check);
		void Add(CDynTexList* list);
	private:
		CTexList m_tex_list;
		CTexPalList m_pal_list;
	};

	class CTexPalette
	{
	public:
	private:
	};

	class CTexHandle
	{
	public:
		char* m_name;
		int m_count;
		unsigned int m_gsAddr;
		CTexture* m_texture;
		bool m_libref;
	};

	class CTextureRelocMgr
	{
	public:
		virtual void AddToBatch(zdb::CTexHandle* handle) const {}
		virtual void ClearAll() {}
		virtual void EndBatchReloc() {}
		virtual void PreGetSprPacket() {}
		virtual void StartBatchReloc() {}
	};

	class CBatchRelocator : public CTextureRelocMgr
	{
	public:
		void AddToBatch(zdb::CTexHandle* handle) const;
		void ClearAll();
		void EndBatchReloc();
		void StartBatchReloc();
		void TakeDrawPacket(void* spr, int qwc);
	};
	
	class CTextureFX
	{
	public:
		static void Init();
	};

	class CLoadImage
	{

	};

	class CRipple
	{
	public:
		static void Init();
	};
}