#include "zvis.h"

#include "gamez/zArchive/zar.h"

namespace zdb
{
	CCamera* CVisual::m_camera = NULL;

	CVisual* CVisual::Create(zar::CZAR& archive)
	{
		CVisual* visual = NULL;
		u32 vtype = 0;
		archive.Fetch("vtype", &vtype);

		if (vtype == 2)
		{
			visual = new CSubMesh();
		}
		else if (vtype == 1)
		{
			visual = new CMesh();
		}
		else if (vtype == 0 || vtype == -1)
		{
			visual = new CVisual();
		}

		if (visual != NULL)
		{
			visual->Read(archive);
		}

		return visual;
	}

	bool CVisual::Read(zar::CZAR& archive)
	{
		archive.Fetch("vparams", this, sizeof(tag_VIS_PARAMS));

		if (m_detail_buff == NULL)
		{
			zfree(m_detail_buff);
		}

		m_detail_buff = NULL;
		m_detail_cnt = 0;

		archive.Fetch("detail_cnt", &m_detail_cnt);
		
		if (m_detail_cnt != 0)
		{
			u32 detail_size = 0;
			archive.Fetch("detail_size", &detail_size);
			m_detail_buff = zmalloc(detail_size);
			archive.Fetch("detail_buff", m_detail_buff, detail_size);

			for (s32 i = 0; i < m_detail_cnt; i++)
			{

			}
		}

		return true;
	}

	bool CVisualVector::Exists(const CVisual* visual)
	{
		for (auto it = begin(); it != end(); it++)
		{
			if (*it == visual)
			{
				return true;
			}
		}

		return false;
	}
}