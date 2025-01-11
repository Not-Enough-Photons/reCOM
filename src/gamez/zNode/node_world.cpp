#include "znode.h"

#define MIN_POOL_SIZE 3000
#define POOL_INCREMENT 100

namespace zdb
{
	CWorld* CWorld::m_world = NULL;
	CCamera* CWorld::m_camera = NULL;

	bool CNodeUniverse::AddNode(CNode* node)
	{
		bool success = false;

		if (!m_locked)
		{
			CNode* universeNode = node;
			int universeSize = size();

			if (universeSize == capacity())
			{
				if (capacity() < MIN_POOL_SIZE)
				{
					reserve(MIN_POOL_SIZE);
				}
				else
				{
					reserve(capacity() + POOL_INCREMENT);
				}
			}

			insert(begin(), universeNode);
			success = true;
		}
		else
		{
			success = false;
		}

		return success;
	}

	void CNodeUniverse::RemoveNode(CNode* node)
	{
		auto it = begin();
		while (it != end())
		{
			if (*it == node)
			{
				break;
			}

			it++;
		}

		*it = NULL;
	}

	CNode* CNodeUniverse::GetElement(int index) const
	{
		CNode* node;

		if (index < 0)
		{
			node = NULL;
		}
		else
		{
			node = NULL;

			if (index <= size())
			{
				node = at(index);
			}
		}

		return node;
	}

	int CNodeUniverse::GetIndex(CNode* node) const
	{
		int index = 0;
		auto it = begin();
		while (it != end())
		{
			if (*it == node)
			{
				break;
			}

			it++;
			index++;
		}

		return index;
	}

	void CWorld::ReserveChildren(int count)
	{
		m_child.reserve(count + m_child.capacity());
	}

	void CWorld::AddChild(CNode* child)
	{
		CWorld* parent = static_cast<CWorld*>(child->m_parent);

		if (parent != this)
		{
			CNode* node = child;

			if (parent != NULL && parent != this)
			{
				parent->DeleteChild(node);
			}

			// m_grid->Insert(node);

			node->m_parent = static_cast<CNode*>(this);

			if (m_child.capacity() == m_child.size())
			{
				m_child.reserve(m_child.capacity() + 100);
			}

			m_child.insert(m_child.begin(), node);

			CNode* temp = node;
			if (node->m_type != 2)
			{
				temp = NULL;
			}

			if (temp != NULL)
			{

			}

			// TODO:
			// Finish the part of this function that inserts "render maps", so the world can
			// dispatch them to the zRenderer.
		}
	}

	void CWorld::AddLandmark(CNode* landmark)
	{
		if (landmark->m_landmark)
		{

		}

		// landmark->RemoveFromParent();
	}
}