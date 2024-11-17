#pragma once
#include "gamez/zNode/node_main.h"

namespace zdb
{
	struct TEXTURE_PARAMS
	{
		unsigned short m_width;
		unsigned short m_height;
		unsigned int m_size;
		unsigned int m_gsaddr;
		unsigned int m_texelBitSize : 8;
		unsigned int m_selectQwc : 8;
		unsigned int m_pal_offset : 8;
		bool m_transparent;
		bool m_palettized;
		bool m_is_mip_child;
		bool m_bumpmap;
		bool m_bilinear;
		bool m_transp_1bit;
		bool m_dynamic;
		bool m_context;
	};

	struct PALETTE_PARAMS
	{
		unsigned int m_gsaddr;
		size_t m_size;
		unsigned int m_format : 8;
		bool m_combo_pal;
		bool m_dynamic;
		unsigned int m_unused : 6;
	};

	class CTexManager
	{
	public:
		static void doAddBuffer(float param_1, float param_2, int param_3, const char* img);
	};

	class CTextureRelocMgr
	{

	};

	class CTexture
	{
	public:
		static void Init();
	private:
		TEXTURE_PARAMS TEXTURE_PARAMS;
		CAssetLib* m_AssetLib;
		const char* m_name;
		void* m_buffer;
		CTexPalette* m_palette;
		long m_gifSelect;
		long m_vuSelect;
		unsigned short m_format;
		unsigned short m_palID;
		unsigned short m_htex_count;
		unsigned short m_gsWords;
		long m_dmaRef;
		long m_dmaRefVu;
		// GL_TEXTURE* gsTex0;
		// GL_MIP_TEXTURE* m_MIP1;
		// GL_MIP_TEXTURE* m_MIP2;
		std::vector<CTexture*> m_reverse_miplist;
		CLoadImage* m_loadimage;
	};

	class CTexPalette
	{
	public:
	private:
	};

	class CTexHandle
	{

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