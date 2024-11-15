#pragma once
#include "Apps/FTS/ai_main.h";

#include "gamez/zNode/node_world.h"
#include "gamez/zAnim/anim_main.h"
#include "gamez/zReader/zrdr_main.h"
#include "gamez/zInput/zin_main.h"
#include "gamez/zTexture/ztex_main.h"

class CUIVariable;
class CUIVariableSpec;
class CUIVarManager;

static CUIVarManager theUIVarManager;

enum UIVAR_LONGEVITY
{
	value_00,
	value_01,
	value_02
};

enum TextColor
{
	WHITE,
	YELLOW,
	BLUE,
	ORANGE,
	RED,
	PURPLE
};

enum TextAlignment
{
	LEFT,
	CENTER,
	RIGHT
};

class C2D
{
public:
	C2D();
	~C2D();

	static zdb::CCamera* m_p2dcamera;

	static void Init();
	static void Open();
public:
	static float m_topx;
	static float m_botx;
	static float m_topy;
	static float m_boty;
	static float m_fXPixel;
	static float m_fYPixel;
public:
	virtual int HandlePad(const CPad* pad, int index);
	virtual void Draw(const CMatrix& mat, zdb::CTextureRelocMgr* manager);
	virtual void Reset();
	virtual void SetActive();
	virtual void SetNormal();
	virtual void SetTrans(float translation);
	virtual void Tick(float delta);
	virtual void TickZAnimCmd(_zanim_cmd_hdr* header, float* delta, bool* enable);

	void Enable(bool enable);
	void Off();

	bool CanHandleInput();
	void SetCanHandleInput(bool enable);
protected:
	CUIVariable* m_uivar;

	bool m_active_and_handling_input;

	bool first;

	bool m_isAA;
	bool m_isTrans;
	bool m_hasTexture;
	bool m_isFrameAlpha;
	bool m_on;
	int m_unused;
};

class C2Dlist
{
public:
	std::list<C2D> m_list;
};

class C2DFade
{
public:
	bool m_fade_enable;
	float m_fade_dx;
	float m_fade_limit;
};

class C2DBitmap : public C2D
{
public:
	C2DBitmap();
	~C2DBitmap();
public:
	void Load(float x, float y, float width, float height, zdb::CTexHandle* handle);
	void Load(float x, float y, zdb::CTexHandle* handle);

	void Draw(const CMatrix& mat, zdb::CTextureRelocMgr* manager);
	void Draw(zdb::CCamera* camera);

	float GetTrans() const;
	void SetTrans(float translation);
private:
	C2DFade m_fade;
	
	int m_x;
	int m_y;

	float m_RGB[2][4];
	float m_NewUV[2][4];

	zdb::CTexHandle* m_pTexHandle;
	int m_iWidth;
	int m_iHeight;
};

class C2DPoly : public C2D
{
public:
	C2DPoly();
};

class CPlainBmp : public C2D
{

};

class C2DMessageString : public C2D
{

};

class C2DFont : public C2D
{
public:
	C2DFont();
};

class C2DMessage_Q : public C2D
{
private:
	C2DFont* m_font;

	C2DBitmap m_background1;
	C2DBitmap m_background2;
	
	float m_scale;
	int m_maxsize;

	int m_top;
	int m_left;

	int m_red;
	int m_blue;
	int m_green;

	float m_maxtrans;
	float m_transstep;

	int m_time;
	
	int m_lowestbottom;
	int m_spacing;
	
	bool m_centered;

	float m_maxlength;
	float m_TtySpeed;

	int m_cur_top;
	float m_moveTime;
	float m_target_top;

	bool m_descends;
	
	int m_XMargin;
	int m_YMargin;

	float m_displayTime;
	bool m_bEnabled;
	float m_Distance;
};

class CZUI
{
public:
	static void InitializeCommandEntry(FT_COMMAND command);
	static const char* GetTeamName(FIRE_TEAM team);
	static const char* GetRawCommandType(FT_COMMAND command);
	static const char* GetCommandDisplayName(FT_COMMAND command);
	static const char* GetProperRegroupDisplay(FT_COMMAND command);
	static const char* GetCommandDescription(FT_COMMAND command);
};

class CInGameWeaponSel : C2D
{
public:
	CInGameWeaponSel();
	~CInGameWeaponSel();

	void HudTick(float delta);
	void GetPrevItem(int param_1);
	void Clear();
	void Init(zdb::CWorld* world);
	void SelectWeapon();
	void SelectEquipment();
	bool CanSelectWeapon(int index) const;
};

class CUIVariable
{
public:
	void Set(_zrdr* reader);
};

class CUIVarManager
{
public:
	CUIVariable* Add(const char* name, _zrdr* reader, UIVAR_LONGEVITY longevity);
};