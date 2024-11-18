#pragma once
// TODO:
// - Connect with rendering APIs like OpenGL, DirectX, and Vulkan
// - Figure what the whole point of the Z renderer is

#include "gamez/zNode/node_main.h"
#include "gamez/zNode/node_world.h"
#include "gamez/zTexture/ztex_main.h"

void zRndrInit();

namespace zdb
{
	typedef struct tag_ZVIS_FOV
	{

	};
}

class CDynTexList
{
public:

};

class CGSTexBuffer
{
public:
	const char* m_name;
	bool m_checkForOverflow;
	unsigned int m_startAddress;
	unsigned int m_nextAddress;
	unsigned int m_endAddress;
	zdb::CAssetLib* m_assetLib;
	long* m_chainp;
	std::vector<void*> m_pktbuf;
	CDynTexList m_dyntex_list;
};

struct tag_TexLoadCmds
{
	CGSTexBuffer* pTexAsset;
	CGSTexBuffer* pTexAssetUsed;
	unsigned int* pWaitTime;
};

class CAlpha
{
private:
	zdb::CCamera* m_camera;
	void* m_visualList;
	void* m_next;
	std::list<void*> m_drawList;
	CDynTexList m_dyntexlist;
};

class CPipe
{
public:
	static void Init();

	void RenderNode(zdb::CNode* node, zdb::tag_ZVIS_FOV* fovTag);
	void RenderUINode(zdb::CNode* node);
	void RenderUINodeRecursive(zdb::CNode* node);
	void RenderWorld(zdb::CWorld* world);
private:
	unsigned int m_texIntIdx;
	unsigned int m_texLoadIdx;

	tag_TexLoadCmds m_texLoadChain[128];

	CGSTexBuffer* m_assetAlpha;
	CGSTexBuffer* m_assetCommon;
	CGSTexBuffer* m_assetCharacter[2];
	CGSTexBuffer* m_assetHUD1;
	CGSTexBuffer* m_assetHUD2;
	CGSTexBuffer* m_assetHUDX;

	zdb::CWorld* m_world;
	zdb::CCamera* m_camera;
	zdb::CCell* m_cell;
	zdb::CNode* m_node;
	zdb::CTexture* m_lightmap;

	bool m_wireframe;
	bool m_terrain;
	bool m_polys;
	bool m_drawShadows;
	bool m_drawReflections;
	bool m_doFog;
	bool m_doUI;
	bool m_drawDI;
	bool m_drawNormal;
	bool m_drawBBox;
	bool m_LODFilter;
	bool m_reticuleDraw;

	float* m_opacity_stack;
	int m_opacity_stack_size;
	int m_opacity_stack_index;

	CAlpha m_alpha;

	std::vector<zdb::CNode*> m_DelayedNodes;
	unsigned int m_delayedNodeNum;
};