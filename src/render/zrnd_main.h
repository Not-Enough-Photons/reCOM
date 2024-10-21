#pragma once
void zRndrInit();

namespace zdb
{
	typedef struct tag_ZVIS_FOV
	{

	};
}

class CPipe
{
public:
	static void Init();

	void RenderNode(zdb::CNode* node, zdb::tag_ZVIS_FOV* fovTag);
	void RenderUINode(zdb::CNode* node);
	void RenderUINodeRecursive(zdb::CNode* node);
	void RenderWorld(zdb::CWorld* world);
};