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

	u32 CGrid::N_ATOMS = 0;

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
		InitNodeParams(this, NULL);
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

	CNode* CNode::Create(const char* name)
	{
		CNode* node = new CNode();
		char* str = NULL;

		if (name)
		{
			str = node->m_name;

			if (str && str != "UNNAMED_NODE")
			{
				zfree(str);
			}

			str = zstrdup("Node");
			node->m_name = str;
		}
		else
		{
			str = node->m_name;

			if (str && str != "UNNAMED_NODE")
			{
				zfree(str);
			}

			if (!str)
			{
				node->m_name = "UNNAMED_NODE";
			}
			else
			{
				str = zstrdup(name);
				node->m_name = str;
			}
		}

		return node;
	}

	void InitNodeParams(tag_NODE_PARAMS* nparams, const tag_NODE_PARAMS* other)
	{
		nparams->m_type                         = other != NULL ? other->m_type : 0;
		nparams->m_active                       = other != NULL ? other->m_active : false;
		nparams->m_dynamic_motion               = other != NULL ? other->m_dynamic_motion : false;
		nparams->m_dynamic_light                = other != NULL ? other->m_dynamic_light : false;
		nparams->m_landmark                     = other != NULL ? other->m_landmark : false;
		nparams->m_light                        = other != NULL ? other->m_light : false;
		nparams->m_prelight                     = other != NULL ? other->m_prelight : false;
		nparams->m_fog                          = other != NULL ? other->m_fog : false;
		nparams->m_transparent                  = other != NULL ? other->m_transparent : false;
		nparams->m_facade                       = other != NULL ? other->m_facade : false;
		nparams->m_reflective                   = other != NULL ? other->m_reflective : false;
		nparams->m_bumpmap                      = other != NULL ? other->m_bumpmap : false;
		nparams->m_hasDI                        = other != NULL ? other->m_hasDI : false;
		nparams->m_region_shift                 = other != NULL ? other->m_region_shift : 0;
		nparams->m_has_visuals_prior_to_export  = other != NULL ? other->m_has_visuals_prior_to_export : false;
		nparams->m_shadow                       = other != NULL ? other->m_shadow : false;
		nparams->m_worldchild                   = other != NULL ? other->m_worldchild : false;
		nparams->m_char_common                  = other != NULL ? other->m_char_common : false;
		nparams->m_NOTUSED                      = other != NULL ? other->m_NOTUSED : false;
		nparams->m_hasVisuals                   = other != NULL ? other->m_hasVisuals : false;
		nparams->m_hasMesh                      = other != NULL ? other->m_hasMesh : false;
		nparams->m_scrolling_texture            = other != NULL ? other->m_scrolling_texture : false;
		nparams->m_light_dynamic                = other != NULL ? other->m_light_dynamic : false;
		nparams->m_light_static                 = other != NULL ? other->m_light_static : false;
		nparams->m_clutter                      = other != NULL ? other->m_clutter : false;
		nparams->m_mtx_is_identity              = other != NULL ? other->m_mtx_is_identity : false;
		nparams->m_use_parent_bbox              = other != NULL ? other->m_use_parent_bbox : false;
		nparams->m_apply_clip                   = other != NULL ? other->m_apply_clip : false;
	}

	bool CNode::AddVisual(CVisual* visual)
	{
		if (visual && !m_visual.Exists(visual))
		{
			visual->m_refcount++;
			m_visual.insert(m_visual.begin(), visual);

			SetParentHasVisuals();

			return true;
		}

		return false;
	}

	bool CNode::AddDI(CDI* di)
	{
		if (di && !m_di.Exists(di))
		{
			di->m_refcount++;
			m_di.insert(m_di.begin(), di);
			m_modified = true;

			return true;
		}

		return false;
	}

	void CNode::AddChild(CNode* node)
	{
		CNode* parent = node->m_parent;
		if (node && parent != this)
		{
			CNode* child = node;
			if (m_type != (u32)TYPE::NODE_TYPE_UNK3)
			{
				if (parent)
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
			if (m_type == (u32)TYPE::NODE_TYPE_UNK3)
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
		if (child)
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

			if (child && nested)
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
		while (!m_child.empty())
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

		if (m_parent && !m_parent->m_modified)
		{
			m_parent->SetParentHasVisuals();
		}

		CModel* vismdl = dynamic_cast<CModel*>(this);

		if (vismdl)
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

	CBBox* CNode::GetBBox()
	{
		if (m_use_parent_bbox)
		{
			return m_parent->GetBBox();
		}

		return &m_bbox;
	}
	
	CMesh* CNode::GetMesh() const
	{
		CVisual* mesh = NULL;

		if (!m_visual.empty())
		{
			mesh = *m_visual.data();
		}

		if (!mesh || !mesh->m_has_lods)
		{
			mesh = NULL;
		}

		return reinterpret_cast<CMesh*>(mesh);
	}

	CGridAtom* CNode::GetAtom(s16 index)
	{
		CGridAtom* atom = NULL;

		if (index < m_AtomAlloc)
		{
			atom = m_Atom[index];
		}

		return atom;
	}

	void CNode::InsertAtom(CGridAtom* atom)
	{
		s16 index = 0;
		m_AtomCnt = index + 1;
		m_Atom[index] = atom;
	}

	void CNode::FreeAtom()
	{
		if (m_Atom)
		{
			zfree(m_Atom);
		}

		m_Atom = NULL;
		m_AtomAlloc = 0;
	}

	CMatrix& CNode::BuildMTW(CMatrix& mat)
	{
		if (m_type == (u32)TYPE::NODE_TYPE_UNK6)
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

		if (str && str != "UNNAMED_NODE")
		{
			zfree(str);
		}

		str = "UNNAMED_NODE";

		if (name)
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

		if (m_nodeEx)
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

		if (!name)
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

	CModel* CModelVector::GetModel(const char* name)
	{
		CModel* model = NULL;
		
		if (name == NULL)
		{
			model = NULL;
		}
		else
		{
			for (auto it = begin(); it != end(); it++)
			{
				if (strcmp(name, (*it)->m_name) == 0)
				{
					model = *it;
					break;
				}
			}
		}

		return model;
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