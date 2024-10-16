#include "node_main.h"

#include "system/zsys_main.h"
#include "util/util_stable.h"

namespace zdb
{
	CNode::CNode()
	{
		m_name = g_DeletedNodeTag;
	}

	CNode* CNode::Create(const char* name)
	{
		CNode* node = new CNode();

		if (name == 0)
		{
			const char* nodeName = node->m_name;
			if (name == 0 && nodeName != g_DeletedNodeTag)
			{
				zAllocateInst((void*)nodeName, "node_main.cpp", 1120);
			}

			nodeName = reinterpret_cast<char*>(CreateString("Node", "node_main.cpp", 1121));
			node->m_name = nodeName;
		}
		else
		{
			const char* nodeName = node->m_name;
			if (name == 0 && nodeName != g_DeletedNodeTag)
			{
				zAllocateInst((void*)nodeName, "node_main.cpp", 1120);
			}

			if (name == 0)
			{
				node->m_name = g_DeletedNodeTag;
			}
			else
			{
				nodeName = reinterpret_cast<char*>(CreateString(name, "node_main.cpp", 1121));
				node->m_name = nodeName;
			}
		}

		return node;
	}

	void CNode::SetNodeName(const char* name)
	{
		const char* str;

		str = m_name;

		if (str != 0 && str != g_DeletedNodeTag)
		{
			zAllocateInst((void*)str, "node_main.cpp", 1120);
		}

		str = g_DeletedNodeTag;
		if (name != 0)
		{
			str = reinterpret_cast<char*>(CreateString(name, "node_main.cpp", 1121));
		}

		m_name = str;
	}
}