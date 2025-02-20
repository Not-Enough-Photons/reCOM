#pragma once
#include <string>

// TODO:
// - Connect with rendering APIs like OpenGL, DirectX, and Vulkan
// - Figure what the whole point of the Z renderer is
// - Experiment with deferred rendering
// - Implement mesh abstractions defined in the game renderer

#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zTexture/ztex.h"

class CPipe;

namespace zar
{
	class CKey;
}

namespace zdb
{
	struct tag_TexLoadCmds;

	class CCamera;
	
	class CNode;
	class CWorld;
	class CCell;

	class CTexture;
	class CGSTexBuffer;

	enum class tag_ZVIS_FOV;
}

enum class _RenderPhase
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
extern u32 numCharactersRendered;
extern f32 bilinearDistance;

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
public:
	static void Multiply(const CMatrix* matrix, bool other);
	
	static CMatrix* m_top;
	static CMatrix* m_pointer;
};

class LODVec : public std::vector<LOD*> {};

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
	zdb::CDynTexList m_dyntexlist;
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
	void Flush();

	zdb::CCamera* m_camera;

	u32 m_texIntIdx;
	u32 m_texLoadIdx;

	zdb::tag_TexLoadCmds m_texLoadChain[128];

	zdb::CGSTexBuffer* m_assetAlpha;
	zdb::CGSTexBuffer* m_assetCommon;
	zdb::CGSTexBuffer* m_assetCharacter[2];
	zdb::CGSTexBuffer* m_assetHUD1;
	zdb::CGSTexBuffer* m_assetHUD2;
	zdb::CGSTexBuffer* m_assetHUDX;

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

namespace zdb
{
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
}


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

class CLOD_Object : public std::vector<zdb::CLOD_band*>
{
public:
	zar::CKey* Read(zdb::CSaveLoad* sload);
	
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