#include "ztex.h"

namespace zdb
{
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
}