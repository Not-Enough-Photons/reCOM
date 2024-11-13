#pragma once
#include "ai/ai_main.h";
#include "node/node_world.h"

#include "zAnim/anim_main.h"
#include "zReader/zrdr_main.h"
	
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
	virtual int HandlePad(const CPad* pad, int index) = 0;
	virtual void Draw(const CMatrix& mat, zdb::CTextureRelocMgr* manager) = 0;
	virtual void Reset() = 0;
	virtual void SetActive() = 0;
	virtual void SetNormal() = 0;
	virtual void SetTrans(float translation) = 0;
	virtual void Tick(float delta) = 0;
	virtual void TickZAnimCmd(_zanim_cmd_hdr* header, float* delta, bool* enable) = 0;

	void Enable(bool enable);
	void Off();

	bool CanHandleInput();
	void SetCanHandleInput(bool enable);
private:
	short visFlags;
	bool handleInput;
};

class C2DBitmap : public C2D
{
public:
	~C2DBitmap();
public:
	void Load(float x, float y, float width, float height, zdb::CTexHandle* handle);
	void Load(float x, float y, zdb::CTexHandle* handle);

	void Draw(const CMatrix& mat, zdb::CTextureRelocMgr* manager);
	void Draw(zdb::CCamera* camera);

	float GetTrans() const;
	void SetTrans(float translation);
private:
	float translation;
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