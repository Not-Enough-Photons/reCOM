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
			str = node->name;
			if (string_exists(str) && str != "UNNAMED_NODE")
			{
				// free(str);
			}

			str = strdup("Node");
			node->name = str;
		}
		else
		{
			str = node->name;

			if (string_exists(str) && str != "UNNAMED_NODE")
			{
				// free(str);
			}

			if (!string_exists(str))
			{
				node->name = "UNNAMED_NODE";
			}
			else
			{
				str = strdup(name);
				node->name = str;
			}
		}

		return node;
	}

	void CNode::AddChild(CNode* node)
	{
		CNode* parent = node->parent;
		if (node != NULL && parent != this)
		{
			CNode* child = node;
			if (nodeType != 3)
			{
				if (parent != NULL)
				{
					parent->DeleteChild(node);
				}

				child->parent = this;
				child->refCount++;
			}

			if (childCount == children.size() && 1000 < childCount)
			{
				children.reserve(childCount + 100);
			}

			children.insert(children.begin(), child);
		}
	}

	int CNode::DeleteChild(CNode* child)
	{
		int count = child->refCount;

		if (nodeVector.Exists(child))
		{
			if (nodeType == 3)
			{
				nodeVector.Remove(child);
				count = -1;
			}
			else
			{
				child->refCount--;
				if (child->refCount <= 0)
				{
					child->refCount = 0;
				}

				count = child->refCount;
				nodeVector.Remove(child);
				child->parent = NULL;
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

	float CCamera::GetScaledRangeSquared(const CPnt3D& point)
	{
		float x = point.x;
		float y = point.y;
		float z = point.z;
		CPnt3D pnt;
		pnt.x = x;
		pnt.y = y;
		pnt.z = z;
		return m_scaledrange * (pnt.z * pnt.z + pnt.x * pnt.x + pnt.y * pnt.y);
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