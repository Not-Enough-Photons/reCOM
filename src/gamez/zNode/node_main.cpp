#include <algorithm>

#include "znode.h"

#include "gamez/zSystem/zsys.h"
#include "gamez/zTexture/ztex.h"
#include "gamez/zUtil/util_stable.h"
#include "gamez/zUtil/zutil.h"

namespace zdb
{
	CNode::CNode()
	{
		m_name = g_DeletedNodeTag;
	}

	CNode* CNode::CreateInstance(CSaveLoad& save)
	{

	}

	CNode* CNode::CreateInstance(const char* name, const CPnt3D& position, const CPnt3D& rotation)
	{

	}

	CNode* CNode::CreateInstance(CModel* model, const CPnt3D& position, const CPnt3D& rotation)
	{

	}

	CNode* CNode::Create(const char* name)
	{
		CNode* node = new CNode();
		const char* str;

		if (!string_exists(name))
		{
			str = node->m_name;
			if (string_exists(str) && str != "UNNAMED_NODE")
			{
				// free(str);
			}

			str = strdup("Node");
			node->m_name = str;
		}
		else
		{
			str = node->m_name;

			if (string_exists(str) && str != "UNNAMED_NODE")
			{
				// free(str);
			}

			if (!string_exists(str))
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

	int CNode::DeleteChild(CNode* child)
	{
		int count = child->m_count;

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
	}

	void CNode::DeleteChildren()
	{
		while (m_child.size() != 0)
		{
			CNode* current = m_child[0];

			int count = DeleteChild(current);

			if (count == 0 && current != NULL)
			{
				current->~CNode();
			}
		}
	}

	float CNode::GetRadius() const
	{
		float radius = 0.0f;

		float minX = m_bbox.m_min.x;
		float minY = m_bbox.m_min.y;
		float minZ = m_bbox.m_min.z;

		float maxX = m_bbox.m_max.x;
		float maxY = m_bbox.m_max.y;
		float maxZ = m_bbox.m_max.z;

		float min = minZ * minZ + minX * minX + minY * minY;
		float max = maxZ * maxZ + maxX * maxX + maxY * maxY;

		if (min <= max)
		{
			radius = max;
		}

		radius = sqrtf(min);
		return radius;
	}

	float CNode::GetRadiusSq() const
	{
		float radius = 0.0f;

		float minX = m_bbox.m_min.x;
		float minY = m_bbox.m_min.y;
		float minZ = m_bbox.m_min.z;

		float maxX = m_bbox.m_max.x;
		float maxY = m_bbox.m_max.y;
		float maxZ = m_bbox.m_max.z;

		float min = minZ * minZ + minX * minX + minY * minY;
		float max = maxZ * maxZ + maxX * maxX + maxY * maxY;

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
		return m_matrix.
	}

	bool CNode::SetActive(bool active)
	{
		m_active = active;
		return m_active;
	}

	CMatrix& CNode::BuildMTW(CMatrix& mat)
	{
		if (m_type == 6)
		{
			// set identity matrix
		}
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

	void CNode::SetPosition(float x, float y, float z)
	{
		m_matrix.m_matrix[3][0] = x;
		m_matrix.m_matrix[3][1] = y;
		m_matrix.m_matrix[3][2] = z;

		UpdateGrid();
		m_modified = true;
		CNodeEx* nodeEx = this->m_nodeEx;

		if (nodeEx != NULL)
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
		CNode* node;

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

CNodeAction::CNodeAction(zdb::CNode* node, CZAnim* animToPlay, CValve* actionValve, zdb::CTexHandle* handle)
{
	this->animations = NULL;
	this->actionAnimation = NULL;
	this->node = node;
	this->actionValve = actionValve;
	this->typeFlag = 6;
	this->iconBitmapHandle = handle;
	this->animVector.insert(animVector.begin(), animToPlay);
	this->actionList = 0;
}