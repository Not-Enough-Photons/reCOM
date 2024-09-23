#pragma once
#include <vector>

namespace zdb
{
	class CNode
	{
	public:
		CNode();

		static bool IS_PLAYER_NODE;
		static bool NODE_ACTIVE;
		static bool NODE_RENDERED;
	};

	/// <summary>
	/// Reference counter for all allocated nodes.
	/// </summary>
	static int Node_Ref_Count = 0;

	/// <summary>
	/// List of all allocated nodes. May change to a linked list in the future.
	/// </summary>
	static std::vector<CNode*> Node_Ref_List;

	class CNodeEx : public CNode
	{

	};

	class CGNode : public CNode
	{

	};
}