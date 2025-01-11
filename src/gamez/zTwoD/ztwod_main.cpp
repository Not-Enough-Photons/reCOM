#include "ztwod.h"

zdb::CCamera* C2D::m_p2dcamera;

f32 C2D::m_topx;
f32 C2D::m_botx;
f32 C2D::m_topy;
f32 C2D::m_boty;
f32 C2D::m_fXPixel;
f32 C2D::m_fYPixel;

C2D::C2D()
{
	first = false;
	m_isAA = false;
	m_isTrans = false;
	m_hasTexture = false;
	m_isFrameAlpha = false;
	m_on = false;

	m_uivar = NULL;
	m_active_and_handling_input = true;
}

void C2D::Init()
{
	m_topx = 1728.0f;
	m_botx = 2368.0f;
	m_topy = 1824.0f;
	m_boty = 2272.0f;
	m_fXPixel = 1.0f;
	m_fYPixel = 1.0f;
}

void C2D::Open()
{
	if (m_p2dcamera == NULL)
	{
		m_p2dcamera = new zdb::CCamera();
	}
}

bool C2D::CanHandleInput()
{
	return m_active_and_handling_input;
}

void C2D::SetCanHandleInput(bool enable)
{
	m_active_and_handling_input = enable;
}

void C2D::Draw(zdb::CCamera* camera)
{
	if (m_on)
	{
		for (auto twod = begin(); twod != end(); twod++)
		{
			(*twod)->Draw(camera);
		}
	}
}

void C2D::Enable(bool enable)
{
	first = enable;
}

void C2D::SetUseFrameBufferAlpha(bool enable)
{
	m_isFrameAlpha = enable;
}

bool C2D::IsOn() const
{
	return m_on == true;
}

void C2D::On()
{
	m_on = true;
}

void C2D::Off()
{
	m_on = false;
}

C2DFade::C2DFade()
{
	m_fade_enable = false;
	m_fade_dx = 0.0f;
	m_fade_limit = 128.0f;
}

C2DPoly::C2DPoly()
{

}

C2DBitmap::C2DBitmap() : C2D(), C2DFade()
{
	m_pTexHandle = NULL;
	m_iWidth = 0;
	m_iHeight = 0;
	m_x = 0;
	m_y = 0;

	m_NewUV[0][0] = 0.01f;
	m_NewUV[0][1] = -0.01f;
	m_NewUV[0][2] = 0.0f;
	m_NewUV[0][3] = 0.0f;
	m_NewUV[1][0] = 0.99f;
	m_NewUV[1][1] = -0.99f;
	m_NewUV[1][2] = 1.0f;
	m_NewUV[1][3] = 0.0f;

	m_RGB[0][0] = 255.0f;
	m_RGB[0][1] = 255.0f;
	m_RGB[0][2] = 255.0f;
	m_RGB[0][3] = 100.0f;
	m_RGB[1][0] = 255.0f;
	m_RGB[1][1] = 255.0f;
	m_RGB[1][2] = 255.0f;
	m_RGB[1][3] = 100.0f;
	m_RGB[0][0] = 128.0f;
	m_RGB[0][1] = 128.0f;
	m_RGB[0][2] = 128.0f;
	m_RGB[1][0] = 128.0f;
	m_RGB[1][1] = 128.0f;
	m_RGB[1][2] = 128.0f;

	SetTrans(128.0f);
}

void C2DBitmap::Load(f32 x, f32 y, f32 width, f32 height, zdb::CTexHandle* handle)
{
	m_pTexHandle = handle;

	m_x = static_cast<s32>(x);
	m_y = static_cast<s32>(y);
	m_iWidth = static_cast<s32>(width) - m_x;
	m_iHeight = static_cast<s32>(height) - m_y;

	if (!m_hasTexture)
	{
		zdb::CTexture* texture = NULL;

		if (handle != NULL)
		{
			texture = handle->m_texture;
		}

		if (texture == NULL && first)
		{
			m_hasTexture = false;
		}
	}
}

void C2DBitmap::Load(f32 x, f32 y, zdb::CTexHandle* handle)
{
	zdb::CTexture* texture = NULL;

	m_pTexHandle = handle;

	if (!m_hasTexture)
	{
		if (handle != NULL)
		{
			texture = handle->m_texture;
		}

		if (texture == NULL && m_hasTexture)
		{
			m_hasTexture = false;
			return;
		}

		return;
	}

	if (m_pTexHandle == NULL)
	{
		texture = NULL;
	}
	else
	{
		texture = m_pTexHandle->m_texture;
	}

	if (texture != NULL)
	{
		m_x = static_cast<s32>(x);
		m_y = static_cast<s32>(y);
		m_iWidth = m_pTexHandle->m_texture->m_width;
		m_iWidth = m_pTexHandle->m_texture->m_height;
	}
}

void C2DBitmap::Draw(const CMatrix& transform, zdb::CTextureRelocMgr* reloc)
{
	zdb::CTexture* texture = NULL;

	if (!IsOn())
	{
		return;
	}

	if (!m_hasTexture)
	{
		if (m_pTexHandle == NULL)
		{
			texture = NULL;
		}
		else
		{
			texture = m_pTexHandle->m_texture;
		}

		if (texture == NULL)
		{
			if (first)
			{
				first = false;
			}

			C2D::Draw(m_p2dcamera);
			return;
		}
	}

	MakePacket(m_p2dcamera, reloc, transform);
	C2D::Draw(m_p2dcamera);
}

void C2DBitmap::Draw(zdb::CCamera* camera)
{

}

void C2DBitmap::TickFade()
{
	float alpha = 0.0f;
	float limit = 0.0f;

	if (m_fade_enable)
	{
		float alpha = m_RGB[0][3] + m_fade_dx;

		if (m_fade_dx < 0.0f)
		{
			float limit = m_fade_limit;

			if ((m_fade_limit <= alpha) && (limit = alpha, alpha < 0.0f))
			{
				limit = 0.0f;
			}
		}
		else
		{
			float limit = m_fade_limit;

			if ((alpha <= m_fade_limit) && (limit = 128.0f, alpha <= 128.0f))
			{
				limit = alpha;
			}
		}

		SetTrans(limit);
	}
}

void C2DBitmap::MakePacket(zdb::CCamera* camera, zdb::CTextureRelocMgr* reloc, const CMatrix& transform)
{
	// TODO:
	// Add more to this function

	reloc->AddToBatch(m_pTexHandle);
}

void C2DBitmap::Reset()
{
	m_x = 0;
	m_y = 0;
	m_pTexHandle = NULL;
	m_iWidth = 0;
	m_iHeight = 0;
}

bool C2DBitmap::GetTrans() const
{
	return m_isTrans;
}

void C2DBitmap::SetTrans(float translation)
{
	m_RGB[0][3] = translation;
	m_RGB[1][3] = translation;
	m_isTrans = true;
}

void C2DBitmap::SetPos(s32 x, s32 y, s32 width, s32 height)
{
	m_x = x;
	m_y = y;
	m_iWidth = width - x;
	m_iHeight = height - y;
}

void C2DBitmap::SetPos(s32 x, s32 y)
{
	zdb::CTexture* texture = NULL;

	if (m_pTexHandle == NULL)
	{
		texture = NULL;
	}
	else
	{
		texture = m_pTexHandle->m_texture;
	}

	if (texture != NULL)
	{
		m_x = x;
		m_y = y;
		m_iWidth = m_pTexHandle->m_texture->m_width;
		m_iWidth = m_pTexHandle->m_texture->m_height;
	}
}

void C2DBitmap::SetUV(f32 u0, f32 v0, f32 u1, f32 v1)
{
	m_NewUV[0][0] = u0;
	m_NewUV[0][1] = -v0;
	m_NewUV[1][0] = u1;
	m_NewUV[1][1] = -v1;
}

void C2DBitmap::SetColor(f32 red, f32 green, f32 blue)
{
	m_RGB[0][0] = red;
	m_RGB[0][1] = green;
	m_RGB[0][2] = blue;
	m_RGB[1][2] = red;
	m_RGB[1][2] = green;
	m_RGB[1][2] = blue;
}