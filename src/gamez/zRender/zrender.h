#pragma once
// TODO:
// - Connect with rendering APIs like OpenGL, DirectX, and Vulkan
// - Figure what the whole point of the Z renderer is
// - Experiment with deferred rendering
// - Implement mesh abstractions defined in the game renderer

#include "zVisual/zvis.h"

#include "gamez/zArchive/zar.h"
#include "gamez/zCamera/zcam.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zNode/znode.h"
#include "gamez/zTexture/ztex.h"

enum LOD
{
	LOW,
	MEDIUM,
	HIGH
};

enum _RenderPhase
{
	WORLD,
	HUD_OBSOLETE,
	CHARSET,
	COMMON,
	CHARSET1,
	CHARSET2,
	CHARSET3,
	CHARSET4,
	CHARSET5,
	CHARSET6,
	CHARSET7,
	CHARSET8,
	ALPHA,
	HUDSET1,
	HUDSET2,
	HUDSETSMALL,
	SHADOW,
	CHARSETCUSTOM,
	NUM_RENDER_PHASES
};

class CPipe;

void zRndrInit();

extern CPipe thePipe;

class CDynTexList : public std::vector<void*> {};

class CGSTexBuffer
{
public:
	const char* m_name;

	bool m_checkForOverflow;

	u32 m_startAddress;
	u32 m_nextAddress;
	u32 m_endAddress;

	zdb::CAssetLib* m_assetLib;

	s64* m_chainp;

	std::vector<void*> m_pktbuf;

	CDynTexList m_dyntex_list;
};

struct tag_TexLoadCmds
{
	CGSTexBuffer* pTexAsset;
	CGSTexBuffer* pTexAssetUsed;
	unsigned int* pWaitTime;
};

/// <summary>
/// Handles transparency.
/// </summary>
class CAlpha
{
	friend class CPipe;
private:
	zdb::CCamera* m_camera;
	void* m_visualList;
	void* m_next;
	std::list<void*> m_drawList;
	CDynTexList m_dyntexlist;
};

/// <summary>
/// Base rendering pipeline for GameZ.
/// </summary>
class CPipe
{
public:
	CPipe();

	static void Init();

	void RenderNode(zdb::CNode* node, zdb::tag_ZVIS_FOV* fovTag);
	void RenderUINode(zdb::CNode* node);
	void RenderUINodeRecursive(zdb::CNode* node);
	void RenderWorld(zdb::CWorld* world);
public:
	zdb::CCamera* m_camera;
private:
	u32 m_texIntIdx;
	u32 m_texLoadIdx;

	tag_TexLoadCmds m_texLoadChain[128];

	CGSTexBuffer* m_assetAlpha;
	CGSTexBuffer* m_assetCommon;
	CGSTexBuffer* m_assetCharacter[2];
	CGSTexBuffer* m_assetHUD1;
	CGSTexBuffer* m_assetHUD2;
	CGSTexBuffer* m_assetHUDX;

	zdb::CWorld* m_world;
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

	f32* m_opacity_stack;
	s32 m_opacity_stack_size;
	s32 m_opacity_stack_index;

	CAlpha m_alpha;

	std::vector<zdb::CNode*> m_DelayedNodes;
	u32 m_delayedNodeNum;
};