#include "node_main.h"

#include "system/zsys_main.h"
#include "util/util_stable.h"

namespace zdb
{
	CNode::CNode()
	{
		name = g_DeletedNodeTag;
	}

	CNode* CNode::Create(const char* name)
	{
		CNode* node = new CNode();

		if (name == 0)
		{
			const char* nodeName = node->name;
			if (name == 0 && nodeName != g_DeletedNodeTag)
			{
				zAllocateInst((void*)nodeName, "node_main.cpp", 1120);
			}

			nodeName = reinterpret_cast<char*>(CreateString("Node", "node_main.cpp", 1121));
			node->name = nodeName;
		}
		else
		{
			const char* nodeName = node->name;
			if (name == 0 && nodeName != g_DeletedNodeTag)
			{
				zAllocateInst((void*)nodeName, "node_main.cpp", 1120);
			}

			if (name == 0)
			{
				node->name = g_DeletedNodeTag;
			}
			else
			{
				nodeName = reinterpret_cast<char*>(CreateString(name, "node_main.cpp", 1121));
				node->name = nodeName;
			}
		}

		return node;
	}

	void CNode::SetName(const char* name)
	{
		const char* str;

		str = name;

		if (str != 0 && str != g_DeletedNodeTag)
		{
			zAllocateInst((void*)str, "node_main.cpp", 1120);
		}

		str = g_DeletedNodeTag;
		if (name != 0)
		{
			str = reinterpret_cast<char*>(CreateString(name, "node_main.cpp", 1121));
		}

		name = str;
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

				}

				child->parent = this;
				child->refCount++;
			}

			if (1000 < size)
			{
				children.reserve(size + 100);
			}

			children.insert(children.begin(), *child);
		}
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

		CPnt3D::Sub(m_pos, pnt);
		return m_scaledrange * (pnt.z * pnt.z + pnt.x * pnt.x + pnt.y * pnt.y);
	}
}