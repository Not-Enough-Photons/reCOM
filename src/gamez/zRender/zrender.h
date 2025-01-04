#pragma once
// TODO:
// - Connect with rendering APIs like OpenGL, DirectX, and Vulkan
// - Figure what the whole point of the Z renderer is
// - Experiment with deferred rendering
// - Implement mesh abstractions defined in the game renderer

#include "vis/zvis.h"

#include "gamez/zArchive/zar.h"
#include "gamez/zCamera/zcam.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zNode/znode.h"
#include "gamez/zTexture/ztex.h"

class Sequence : std::vector<void*> {};

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

void zRndrInit();

class CDynTexList : public std::vector<void*> {};

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

/// <summary>
/// Handles transparency.
/// </summary>
class CAlpha
{
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

struct Props
{
	int m_refCount;
	Sequence m_textureSeq;
	Sequence m_colorSeq;
	Sequence m_scaleSeq;

	zdb::CModel* m_model;
	float m_friction;
	CPnt4D m_accelW;
	float m_windFactor;
	float m_priority;
	float m_nearFade1;
	float m_nearFade2;
	float m_nearFade2;
	float m_farFade1;
	float m_farFade2;
	float m_invNearFade;
	float m_invFarFade;
	float m_visualDensity;
	bool m_checkFade;
};