#include <algorithm>

#include "znode.h"

#include "gamez/zRender/zVisual/zvis.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zTexture/ztex.h"
#include "gamez/zUtil/util_stable.h"
#include "gamez/zUtil/zutil.h"

namespace zdb
{
	u32 numNodes = 0;

	CNode::CNode()
	{
		m_matrix = CMatrix::identity;

		m_name = NULL;
		m_count = 0;
		m_model = NULL;
		m_modelname = NULL;
		m_vid = 0;
		m_nodeEx = NULL;
		m_Atom = NULL;
		m_AtomCnt = 0;
		m_AtomAlloc = 0;
		m_TickNum = -1;
		m_Opacity = 1.0f;
		InitNodeParams();
		m_customGlobalLight = false;
		m_flatten = false;
		m_modified = false;
		m_parent = false;
		m_unused = 0;
		m_frameRendered = false;
		m_region_mask = 0;

		m_bbox.m_min = CPnt3D::zero;
		m_bbox.m_max = CPnt3D::zero;

		if (NodeUniverse != NULL)
		{
			NodeUniverse->AddNode(this);
		}

		numNodes++;
		m_name = "UNNAMED_NODE";
	}

	CNode* CNode::CreateInstance(const char* name, const CPnt3D& position, const CPnt3D& rotation)
	{
		return NULL;
	}

	CNode* CNode::CreateInstance(CModel* model, const CPnt3D& position, const CPnt3D& rotation)
	{
		return NULL;
	}

	CNode* CNode::Create(const char* name)
	{
		CNode* node = new CNode();
		char* str = NULL;

		if (name != NULL)
		{
			str = node->m_name;

			if (str != 0 && str != "UNNAMED_NODE")
			{
				zfree(str);
			}

			str = strdup("Node");
			node->m_name = str;
		}
		else
		{
			str = node->m_name;

			if (str != NULL && str != "UNNAMED_NODE")
			{
				zfree(str);
			}

			if (str == NULL)
			{
				node->m_name = "UNNAMED_NODE";
			}
			else
			{
				str = strdup(name);
				node->m_name = str;
			}
		}

		return node;
	}

	void CNode::InitNodeParams(tag_NODE_PARAMS* other)
	{
		m_type                         = other != NULL ? other->m_type : 0;
		m_active                       = other != NULL ? other->m_active : false;
		m_dynamic_motion               = other != NULL ? other->m_dynamic_motion : false;
		m_dynamic_light                = other != NULL ? other->m_dynamic_light : false;
		m_landmark                     = other != NULL ? other->m_landmark : false;
		m_light                        = other != NULL ? other->m_light : false;
		m_prelight                     = other != NULL ? other->m_prelight : false;
		m_fog                          = other != NULL ? other->m_fog : false;
		m_transparent                  = other != NULL ? other->m_transparent : false;
		m_facade                       = other != NULL ? other->m_facade : false;
		m_reflective                   = other != NULL ? other->m_reflective : false;
		m_bumpmap                      = other != NULL ? other->m_bumpmap : false;
		m_hasDI                        = other != NULL ? other->m_hasDI : false;
		m_region_shift                 = other != NULL ? other->m_region_shift : 0;
		m_has_visuals_prior_to_export  = other != NULL ? other->m_has_visuals_prior_to_export : false;
		m_shadow                       = other != NULL ? other->m_shadow : false;
		m_worldchild                   = other != NULL ? other->m_worldchild : false;
		m_char_common                  = other != NULL ? other->m_char_common : false;
		m_NOTUSED                      = other != NULL ? other->m_NOTUSED : false;
		m_hasVisuals                   = other != NULL ? other->m_hasVisuals : false;
		m_hasMesh                      = other != NULL ? other->m_hasMesh : false;
		m_scrolling_texture            = other != NULL ? other->m_scrolling_texture : false;
		m_light_dynamic                = other != NULL ? other->m_light_dynamic : false;
		m_light_static                 = other != NULL ? other->m_light_static : false;
		m_clutter                      = other != NULL ? other->m_clutter : false;
		m_mtx_is_identity              = other != NULL ? other->m_mtx_is_identity : false;
		m_use_parent_bbox              = other != NULL ? other->m_use_parent_bbox : false;
		m_apply_clip                   = other != NULL ? other->m_apply_clip : false;
	}

	bool CNode::Read(CSaveLoad& sload)
	{
		zar::CKey* nodekey = sload.m_zfile.GetOpenKey();
		SetName(nodekey->GetName());

		sload.m_zfile.Fetch("matrix", &m_matrix, sizeof(CMatrix));
		sload.m_zfile.Fetch("bbox", &m_bbox, sizeof(CBBox));

		zar::CKey* viskey = sload.m_zfile.OpenKey("visuals");

		if (viskey != NULL)
		{
			ReserveVisuals(viskey->GetSize());

			auto it = viskey->begin();

			while (it != viskey->end())
			{
				zar::CKey* k = sload.m_zfile.OpenKey(k);

				if (k != NULL)
				{
					CVisual* visual = CVisual::Create(sload.m_zfile);
					AddVisual(visual);
					sload.m_zfile.CloseKey(k);
				}
			}
		}

		return true;
	}

	bool CNode::AddVisual(CVisual* visual)
	{
		if (visual != NULL && !m_visual.Exists(visual))
		{
			visual->m_instance_cnt++;
			m_visual.insert(m_visual.begin(), visual);

			SetParentHasVisuals();
		}

		return true;
	}

	void CNode::AddChild(CNode* node)
	{
		CNode* parent = node->m_parent;
		if (node != NULL && parent != this)
		{
			CNode* child = node;
			if (m_type != 3)
			{
				if (parent != NULL)
				{
					parent->DeleteChild(node);
				}

				child->m_parent = this;
				child->m_count++;
			}

			if (m_count == m_child.size() && 1000 < m_count)
			{
				m_child.reserve(m_count + 100);
			}

			m_child.insert(m_child.begin(), child);
		}
	}

	s32 CNode::DeleteChild(CNode* child)
	{
		s32 count = child->m_count;

		if (m_child.Exists(child))
		{
			if (m_type == 3)
			{
				m_child.Remove(child);
				count = -1;
				m_flatten = true;
			}
			else
			{
				child->m_count--;

				if (child->m_count < 0)
				{
					child->m_count = 0;
				}

				count = child->m_count;

				m_child.Remove(child);

				child->m_parent = NULL;

				m_flatten = true;
			}
		}
		
		return 0;
	}

	CNode* CNode::FindChild(CNode* child, bool nested)
	{
		if (child == NULL)
		{
			return NULL;
		}
		else
		{
			for (auto it = m_child.begin(); it != m_child.end(); it++)
			{
				if (*it == child)
				{
					return *it;
				}
			}

			if (nested)
			{
				for (auto it = m_child.begin(); it != m_child.end(); it++)
				{
					(*it)->FindChild(child, nested);
				}
			}
		}
	}

	CNode* CNode::FindChild(const char* name, bool nested)
	{
		if (name == 0)
		{
			return NULL;
		}
		else
		{
			zdb::CNode* child = NULL;
			size_t length = strlen(name);

			for (auto it = m_child.begin(); it != m_child.end(); it++)
			{
				child = *it;
				size_t childStringLength = strlen(child->m_name);

				if (length == childStringLength && strcmp(child->m_name, name) == 0)
				{
					child = *it;
				}
			}

			if (child == NULL && nested)
			{
				for (auto it = m_child.begin(); it != m_child.end(); it++)
				{
					child = *it;
					size_t childStringLength = strlen(child->m_name);

					if (length == childStringLength && strcmp(child->m_name, name) == 0)
					{
						child = *it;
					}
				}
			}
		}
	}

	void CNode::DeleteChildren()
	{
		while (m_child.size() != 0)
		{
			CNode* current = m_child.front();

			s32 count = DeleteChild(current);

			if (count == 0 && current != NULL)
			{
				// current->~CNode();
			}
		}
	}

	void CNode::ReserveChildren(size_t size)
	{
		m_child.reserve(size);
	}

	void CNode::ReserveDI(size_t size)
	{
		// m_di.reserve(size);
	}

	void CNode::ReserveVisuals(size_t size)
	{
		m_visual.reserve(size);
	}

	void CNode::SetParentHasVisuals()
	{
		m_modified = true;

		if (m_parent != NULL && !m_parent->m_modified)
		{
			m_parent->SetParentHasVisuals();
		}

		CModel* vismdl = dynamic_cast<CModel*>(this);

		if (vismdl != NULL)
		{
			// TODO:
			// Use CRefList for iteration on visuals
		}
	}

	f32 CNode::GetRadius() const
	{
		f32 radius = 0.0f;

		f32 minX = m_bbox.m_min.x;
		f32 minY = m_bbox.m_min.y;
		f32 minZ = m_bbox.m_min.z;

		f32 maxX = m_bbox.m_max.x;
		f32 maxY = m_bbox.m_max.y;
		f32 maxZ = m_bbox.m_max.z;

		f32 min = minZ * minZ + minX * minX + minY * minY;
		f32 max = maxZ * maxZ + maxX * maxX + maxY * maxY;

		if (min <= max)
		{
			radius = max;
		}

		radius = sqrtf(min);
		return radius;
	}

	f32 CNode::GetRadiusSq() const
	{
		f32 radius = 0.0f;

		f32 minX = m_bbox.m_min.x;
		f32 minY = m_bbox.m_min.y;
		f32 minZ = m_bbox.m_min.z;

		f32 maxX = m_bbox.m_max.x;
		f32 maxY = m_bbox.m_max.y;
		f32 maxZ = m_bbox.m_max.z;

		f32 min = minZ * minZ + minX * minX + minY * minY;
		f32 max = maxZ * maxZ + maxX * maxX + maxY * maxY;

		if (min <= max)
		{
			radius = max;
		}

		return radius;
	}

	CPnt3D* CNode::GetScale(CPnt3D* scale) const
	{
		scale->x = m_matrix.m_matrix[0][0];
		scale->y = m_matrix.m_matrix[1][1];
		scale->z = m_matrix.m_matrix[2][2];
		return scale;
	}

	CPnt3D* CNode::GetRotation(const CPnt3D* rotation) const
	{
		return NULL;
	}

	bool CNode::SetActive(bool active)
	{
		m_active = active;
		return m_active;
	}

	void CNode::SetModel(CModel* model)
	{

	}

	CMatrix& CNode::BuildMTW(CMatrix& mat)
	{
		if (m_type == 6)
		{
			// set identity matrix
		}

		return CMatrix();
	}

	short CNode::Release()
	{
		m_count--;

		if (m_count < 0)
		{
			m_count = 0;
		}

		return m_count;
	}

	void CNode::SetName(const char* name)
	{
		char* str = m_name;

		if (str != NULL && str != "UNNAMED_NODE")
		{
			zfree(str);
		}

		str = "UNNAMED_NODE";

		if (name != NULL)
		{
			str = zstrdup(name);
		}

		m_name = str;
	}

	void CNode::SetPosition(f32 x, f32 y, f32 z)
	{
		m_matrix.m_matrix[3][0] = x;
		m_matrix.m_matrix[3][1] = y;
		m_matrix.m_matrix[3][2] = z;

		UpdateGrid();
		m_modified = true;

		if (m_nodeEx != NULL)
		{
			m_nodeEx->OnMove(this);
		}
	}

	bool CNodeVector::Exists(const CNode* node) const
	{
		auto it = begin();
		auto last = end();

		while (it != last)
		{
			if (*it == node)
			{
				break;
			}

			it++;
		}

		return it != last;
	}

	CNode* CNodeVector::GetNode(const char* name) const
	{
		CNode* node = NULL;

		if (name == 0)
		{
			return NULL;
		}
		else
		{
			auto it = begin();
			auto last = end();

			while (it != last)
			{
				CNode* node = *it;
				bool found = false;

				if (node != NULL && node->m_name != 0)
				{
					found = strcmp(name, node->m_name);
				}

				if (found)
				{
					break;
				}
			}

			if (it != last)
			{
				node = *it;
			}
		}

		return node;
	}

	bool CNodeVector::Remove(const CNode* node)
	{
		auto it = begin();
		auto last = end();

		for (; it != last; it++)
		{
			if (*it == node)
			{
				break;
			}
		}

		const CNode* found = node;

		if (it != last)
		{
			it = std::remove_copy(it + 1, last, it, found);
		}

		erase(it, last);

		return it != last;
	}
}

//CNodeAction::CNodeAction(zdb::CNode* node, CZAnim* animToPlay, CValve* actionValve, zdb::CTexHandle* handle)
//{
//	this->animations = NULL;
//	this->actionAnimation = NULL;
//	this->node = node;
//	this->actionValve = actionValve;
//	this->typeFlag = 6;
//	this->iconBitmapHandle = handle;
//	this->animVector.insert(animVector.begin(), animToPlay);
//	this->actionList = 0;
//}