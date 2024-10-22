#pragma once
// Copyright (c) Zipper Interactive, 1999 - 2002
// Reverse engineered by Adam of Not Enough Photons

// TODO:
// - Connect with rendering APIs like OpenGL, DirectX, and Vulkan
// - Figure what the whole point of the Z renderer is

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