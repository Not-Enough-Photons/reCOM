#include <GL/glew.h>

#include "zvis.h"

#include "gamez/zArchive/zar.h"
#include "gamez/zNode/znode.h"
#include "gamez/zRender/zrender.h"
#include "gamez/zRender/zShader/zshader.h"

s32 node_index = 0;

void hookupMesh(zar::CZAR* archive, zdb::CModel* model)
{
	
}

void hookupVisuals(zar::CZAR* archive, zar::CKey* key, zdb::CNode* node, zdb::CModel* model, zdb::CVisBase* vis)
{
	
}

void hookupVisuals(zar::CZAR* archive, zdb::CModel* model)
{
	zdb::CVisBase* vis = NULL;
	zdb::CMesh* mesh = model->GetMesh();

	if (!mesh)
	{
		node_index = -1;

		zar::CKey* modelkey = archive->OpenKey(model->m_name);

		if (modelkey)
		{
			vis = new zdb::CVisBase(modelkey->GetSize());
			
			if (!archive->FetchLIP(modelkey, reinterpret_cast<void**>(vis)))
			{
				if (modelkey && !vis->m_active)
				{
					if (vis->m_data_buffer)
					{
						zfree(vis->m_data_buffer);
					}

					vis->m_data_buffer = NULL;
				}

				zdb::CVisBase::m_instance_count--;
				delete vis;
			}
			else
			{
				// hookupVisuals(modelkey, model, model, vis);
			}

			archive->CloseKey(modelkey);
		}
	}
	else
	{
		hookupMesh(archive, model);
	}
}

namespace zdb
{
	u32 CVisBase::m_instance_count = 0;

	CPnt4D CVisual::m_basefog_color = CPnt4D::zero;
	
	CCamera* CVisual::m_camera = NULL;

	CVisBase::CVisBase(size_t size)
	{
		m_data_buffer = NULL;
		m_buffer_count = 0;
		m_data_size = size;
		CVisBase::m_instance_count++;
		m_active = true;
	}
	
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

	bool CVisual::DrawLOD(zdb::CLOD_band* lod, f32 range, f32* distance)
	{
		bool inrange = false;

		if (lod->m_minRangeNearSq < range && range < lod->m_maxRangeFarSq)
		{
			if (lod->m_minFade)
			{
				inrange = true;
			}
			else if (range < lod->m_minRangeFarSq || (inrange = true, lod->m_maxRangeFarSq < range))
			{
				if (lod->m_minFade || lod->m_minRangeNearSq < range)
				{
					inrange = true;
					if (lod->m_maxFade)
					{
						if (lod->m_maxRangeNearSq <= range)
						{
							inrange = true;
							*distance = *distance * lod->m_minInvDeltaRangeSq * (range - lod->m_minRangeNearSq);
						}
					}
				}
			}
		}

		return inrange;
	}

	
	void CVisual::Render()
	{
		if (m_renderState != 0)
		{
			VuUpdate(1.0f);
		}
	}

	void CVisual::VuUpdate(f32 opacity)
	{
		glUseProgram(m_shader->m_ID);
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	
	u32 CVisual::Release()
	{
		m_instance_cnt--;
		return m_instance_cnt;
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