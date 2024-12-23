#include "znode.h"
#include "node_world.h"

#define MIN_POOL_SIZE 3000
#define POOL_INCREMENT 100

namespace zdb
{
	bool CNodeUniverse::AddNode(CNode* node)
	{
		bool success = false;

		if (!m_locked)
		{
			CNode* addNode = node;
			int capacity = this->capacity;

			if (capacity == nodes.capacity())
			{
				if (capacity < MIN_POOL_SIZE)
				{
					nodes.reserve(MIN_POOL_SIZE);
				}
				else
				{
					nodes.reserve(capacity + POOL_INCREMENT);
				}
			}

			nodes.insert(nodes.begin(), addNode);
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
		CNode** cur = this->head;
		CNode** tail = this->tail;

		while (cur != tail)
		{
			if (*cur == node)
			{
				break;
			}

			cur++;
		}

		*cur = NULL;
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

			if (index <= nodes.size())
			{
				node = nodes.at(index);
			}
		}

		return node;
	}

	int CNodeUniverse::GetIndex(CNode* node) const
	{
		int index = 0;
		CNode** cur = this->head;
		CNode** tail = this->tail;

		while (cur != tail)
		{
			if (*cur == node)
			{
				break;
			}

			cur++;
			index++;
		}

		return index;
	}

	void CWorld::ReserveChildren(int count)
	{
		children.reserve(count + expandSize);
	}

	void CWorld::AddChild(CNode* child)
	{
		// Ass.
		CWorld* parent = reinterpret_cast<CWorld*>(child->parent);

		if (parent != this)
		{
			CNode* node = child;

			if (parent != NULL && parent != this)
			{
				parent->DeleteChildren();
			}

			grid->Insert(node);

			// Ass.
			node->parent = reinterpret_cast<CNode*>(this);

			if (expandSize == children.size())
			{
				children.reserve(expandSize + 100);
			}

			children.insert(children.begin(), node);

			CNode* temp = node;
			if (node->nodeType != 2)
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
		if (landmark->renderFlags)

		landmark->RemoveFromParent();
	}
}