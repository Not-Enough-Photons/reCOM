#include "ztex.h"

#include "freebsd/strcasecmp.h"

#include "gamez/zArchive/zar.h"
#include "gamez/zSave/zsave.h"
#include "gamez/zVideo/zvid.h"

namespace zdb
{
	u32 CTexture::m_baseAddress = 0;
	u32 CTexture::m_endAddress = 0;
	u32 CTexture::m_startAddress = 0;
	
	CTexture::CTexture(const char* name)
	{
		m_name = "UNNAMED_TEX";
		m_palette = NULL;

		m_texelBitSize = 0;
		m_selectQwc = 0;
		m_pal_offset = 0;
		m_transparent = false;
		m_palettized = false;
		m_is_mip_child = false;
		m_bumpmap = false;
		m_bilinear = false;
		m_transp_1bit = false;
		m_dynamic = false;
		m_context = false;

		m_width = 0;
		m_height = 0;
		m_gsaddr = 0;
		m_palID = 0;

		m_AssetLib = NULL;
		m_htex_count = 0;

		if (m_name && m_name != "UNNAMED_TEX")
		{
			zfree(m_name);
		}

		m_name = "UNNAMED_TEX";

		if (name)
		{
			m_name = zstrdup(name);
		}
	}

	CTexture::~CTexture()
	{
		
	}

	void CTexture::Init()
	{
		m_baseAddress = zVid.textureBaseAddr;
		m_endAddress = zVid.textureEndAddr;
		m_startAddress = zVid.textureBaseAddr + 0x200;
	}

	bool CTexture::Read(zdb::CSaveLoad& sload)
	{
		bool success = false;
		_word128* lipbuf = NULL;
		auto texdat = sload.m_zfile.FindKey("texdat");

		if (texdat && sload.m_zfile.FetchLIP(texdat, (void**)&lipbuf))
		{
			success = true;
			memcpy(this, lipbuf, sizeof(TEXTURE_PARAMS));
			void* texalloc = zmalloc(sizeof(CTexture));
			u32 ofs = lipbuf[1].u32[0];
			m_buffer = &lipbuf->u8[ofs] + 24;
		}

		return success;
	}
	
	bool CTexture::Read(zar::CZAR& archive)
	{
		bool success = false;
		_word128* lipbuf = NULL;
		auto texdat = archive.FindKey("texdat");

		if (texdat && archive.FetchLIP(texdat, (void**)&lipbuf))
		{
			success = true;
			memcpy(this, lipbuf, sizeof(TEXTURE_PARAMS));
			u32 ofs = lipbuf[1].u32[0];
			m_buffer = lipbuf->u8 + ofs + 0x18;
		}

		return success;
	}
	
	u16 CTexture::Release_HTEX()
	{
		u16 count = m_htex_count;
		m_htex_count = count - 1;
		return count - 1;
	}

	CTexHandle* CTexHandle::Create(CTexture* texture)
	{
		CTexHandle* handle = new CTexHandle();

		handle->m_name = NULL;
		handle->m_count = 0;
		handle->m_texture = NULL;
		handle->m_libref = false;

		if (handle->m_texture != NULL)
		{
			handle->m_texture->Release_HTEX();
		}

		handle->m_texture = texture;

		if (texture != NULL)
		{
			char* name = texture->m_name;

			if (handle->m_name != NULL)
			{
				zfree(handle->m_name);
			}

			handle->m_name = NULL;

			if (name == NULL)
			{
				handle->m_name = NULL;
			}
			else
			{
				handle->m_name = strdup(name);
			}

			texture->m_htex_count++;
		}

		handle->m_count++;
		return handle;
	}

	void CDynTexList::Add(CTexPalette* palette, bool check)
	{

	}

	void CDynTexList::Add(CTexHandle* handle, bool check)
	{

	}

	void CDynTexList::Add(CDynTexList* list)
	{

	}

	CGSTexBuffer::CGSTexBuffer()
	{
		m_checkForOverflow = true;
		m_startAddress = 0;
		m_nextAddress = 0;
		m_endAddress = 0;
		m_assetLib = NULL;
		m_chainp = NULL;
		m_name = NULL;
	}

	void CGSTexBuffer::Hookup(CAssetLib* lib)
	{
		
	}

	CTexHandle* CTexList::GetHandle(const char* name)
	{
		auto it = begin();

		while (it != end())
		{
			CTexHandle* handle = *it;

			if (!handle->m_texture || !handle->m_name)
			{
				continue;
			}

			if (strcasecmp(handle->m_name, name) == 0)
			{
				break;
			}
			
			++it;
		}

		return *it;
	}

}
