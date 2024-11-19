#include <algorithm>

#include "node_main.h"

#include "gamez/zSystem/zsys_main.h"
#include "gamez/zTexture/ztex_main.h"
#include "gamez/zUtil/util_stable.h"
#include "gamez/zUtil/util_main.h"

namespace zdb
{
	CNode::CNode()
	{
		name = g_DeletedNodeTag;
	}

	CNode* CNode::CreateInstance(CSaveLoad& save)
	{
		CWorld world = CWorld::m_world;
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
			if (tag_NODE_PARAMS.m_type != 3)
			{
				if (parent != NULL)
				{
					parent->DeleteChild(node);
				}

				child->m_parent = this;
				child->m_count++;
			}

			if (m_count == m_child.m_nodes.size() && 1000 < m_count)
			{
				m_child.m_nodes.reserve(m_count + 100);
			}

			m_child.m_nodes.insert(m_child.m_nodes.begin(), child);
		}
	}

	int CNode::DeleteChild(CNode* child)
	{
		int count = child->m_count;

		if (m_child.Exists(child))
		{
			if (p.m_type == 3)
			{
				m_child.Remove(child);
				count = -1;
			}
			else
			{
				child->m_count--;
				if (child->m_count <= 0)
				{
					child->m_count = 0;
				}

				count = child->m_count;
				m_child.Remove(child);
				child->m_parent = NULL;
				// some flag BS
				// hierarchyFlags = hierarchyFlags & 0xfd | 2;
			}
		}
	}

	void CNode::DeleteChildren()
	{
		while (childCount != 0)
		{
			CNode* current = *children.begin();
			int count = DeleteChild(current);
			if (count == 0 && current != NULL)
			{
				current->~CNode();
			}
		}
	}

	float CNode::GetRadius() const
	{
		float radius = (radiusX + radiusX) * (radiusY + radiusY) * (radiusZ + radiusZ);
		float maxRadius = (radiusMaxX + radiusMaxX) * (radiusMaxY + radiusMaxY) * (radiusMaxZ + radiusMaxZ);

		if (radius <= maxRadius)
		{
			radius = maxRadius;
		}

		radius = sqrtf(radius);
		return radius;
	}

	float CNode::GetRadiusSq() const
	{
		float radius = (radiusX + radiusX) * (radiusY + radiusY) * (radiusZ + radiusZ);
		float maxRadius = (radiusMaxX + radiusMaxX) * (radiusMaxY + radiusMaxY) * (radiusMaxZ + radiusMaxZ);

		if (radius <= maxRadius)
		{
			radius = maxRadius;
		}

		return radius;
	}

	CPnt3D* CNode::GetScale(CPnt3D* scale) const
	{
		scale->x = scaleX;
		scale->y = scaleY;
		scale->z = scaleZ;
		return scale;
	}

	bool CNode::SetActive(bool active)
	{
		char flags = stateFlags;
		stateFlags = flags & 0xfe | active;

		// The first bit might be the bit that determines if its active?
		return (flags & 1) != 0;
	}

	void CNode::SetPosition(float x, float y, float z)
	{
		posX = x;
		posY = y;
		posZ = z;

		UpdateGrid();
		field82_0x9a = field82_0x9a & 0xfd | 2;
		CNodeEx* nodeEx = this->nodeEx;

		if (nodeEx != NULL)
		{

		}
	}

	bool CNodeVector::Exists(const CNode* node) const
	{
		std::vector<CNode*>::const_iterator first = this->nodes.begin();
		std::vector<CNode*>::const_iterator last = this->nodes.end();

		while (first != last)
		{
			if (*first == node)
			{
				break;
			}

			first++;
		}

		return first != last;
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
			std::vector<CNode*>::const_iterator first = this->nodes.begin();
			std::vector<CNode*>::const_iterator last = this->nodes.end();

			while (first != last)
			{
				bool found = false;

				if (*first != NULL && (*first)->name != 0)
				{
					found = strcmp(name, (*first)->name);
				}

				if (found)
				{
					break;
				}
			}

			if (first != last)
			{
				node = *first;
			}
		}

		return node;
	}

	bool CNodeVector::Remove(const CNode* node)
	{
		std::vector<CNode*>::const_iterator first = this->nodes.begin();
		std::vector<CNode*>::const_iterator last = this->nodes.end();

		for (; first != last; first++)
		{
			if (*first == node)
			{
				break;
			}
		}

		const CNode* found = node;

		if (first != last)
		{
			first = std::remove_copy(first + 1, last, first, found);
		}

		nodes.erase(first, last);

		return first != last;
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