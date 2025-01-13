#pragma once
#include <string>

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

class CPipe;

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

extern CPipe thePipe;

struct LOD
{
	std::string m_file;
	std::string m_name;
	f32 m_dist;
};

struct BLENDMODE
{
	u32 mode1;
	u32 mode2;
};

/// <summary>
/// Matrix transform stack.
/// </summary>
class CStack
{

};

class LODVec : public std::vector<LOD*> {};

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
	u32* pWaitTime;
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
	u32 RenderWorld(zdb::CWorld* world);
public:
	zdb::CCamera* m_camera;

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
	bool m_simpletrans;
	bool m_drawCharacters;
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

class CLOD_band
{
public:
	f32 m_minRangeNearSq;
	f32 m_minRangeFarSq;
	f32 m_minInvDeltaRangeSq;
	f32 m_maxRangeNearSq;
	f32 m_maxRangeFarSq;
	u32 m_minFade : 1;
	u32 m_maxFade : 1;
	u32 m_unused : 30;
	u32 m_padding;
};

class CMaterial_band
{
public:
	CPnt3D m_rgb;
	f32 m_opacity;
	f32 m_intensity;
	u8 m_material_id;
	BLENDMODE* m_pBlendmode;
};

class CSubSurf_band
{
public:
	f32 m_distanceSq_Near;
	f32 m_distanceSq_Far;
	s32 m_density_Near;
	s32 m_density_Far;
	f32 m_pushFactor;
};

class CPreLight_band
{
public:
	CPnt3D m_position;
	CPnt3D m_color;
	f32 m_minRange;
	f32 m_maxRangeSq;
	bool m_dynamic;
	// CFilterPlane -- idk what this type is, it's a std::list of something
};

class CProjectedMap_band
{
	// TODO:
	// guess what is inside this class
	// CodeWarrior doesn't have a definition for this for some reason
public:
};

class CScrollingTexture_band
{
public:
	char m_modelname[256];
	char m_nodename[256];
	f32 m_du;
	f32 m_dv;
};

class CLOD_Object : public std::vector<CLOD_band*>
{
private:
	s32 m_bandMax;
};

class CMaterial_Object : public std::vector<CMaterial_band*>
{
private:
	s32 m_bandMax;
};

class CSubSurf_Object : public std::vector<CSubSurf_band*>
{
private:
	s32 m_bandMax;
};

class CPreLight_Object : public std::vector<CPreLight_band*>
{
private:
	s32 m_bandMax;
};

class CProjectedMap_Object : public std::vector<CProjectedMap_band*>
{
private:
	s32 m_bandMax;
};

class CScrollingTexture_Object : public std::vector<CScrollingTexture_band*>
{
private:
	s32 m_bandMax;
};