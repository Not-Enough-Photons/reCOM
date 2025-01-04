#pragma once
#include "gamez/zAnim/zanim.h"
#include "gamez/zCamera/zcam.h"
#include "gamez/zInput/zinput.h"
#include "gamez/zSystem/zsys.h"

class C2D;
class CUIVariable;

class C2Dlist : public std::list<C2D*> {};

class C2D : public C2Dlist
{
public:
	C2D();

	static void Init();
	static void Open();

	static zdb::CCamera* m_p2dcamera;

	static f32 m_topx;
	static f32 m_botx;
	static f32 m_topy;
	static f32 m_boty;
	static f32 m_fXPixel;
	static f32 m_fYPixel;
public:
	virtual void Draw(const CMatrix& transform, zdb::CTextureRelocMgr* manager) {}
	virtual void Draw(zdb::CCamera* camera);
	virtual void Reset() {}
	virtual void Tick(float dT) {}
	virtual bool TickZAnimCmd(_zanim_cmd_hdr* header, float* delta, bool* enable) { return false; }
	virtual bool ParseZAnimCmd(_zrdr* reader) { return false; }
	virtual bool HandlePad(const CPad* pad, int index) { return false; }

	virtual void SetActive() {}
	virtual void SetNormal() {}
	virtual void SetTrans(float translation) {}
	virtual void SetUseFrameBufferAlpha(bool enable);
	virtual void SetMapOffset(int x, int y) {}

	void Enable(bool enable);
	void On();
	void Off();
	
	bool IsOn() const;
	bool CanHandleInput();
	void SetCanHandleInput(bool enable);
protected:
	CUIVariable* m_uivar;

	bool m_active_and_handling_input;

	u32 first : 1;
	u32 m_isAA : 1;
	u32 m_isTrans : 1;
	u32 m_hasTexture : 1;
	u32 m_isFrameAlpha : 1;
	u32 m_on : 1;
	u32 m_unused : 26;
};

class C2DFade
{
public:
	C2DFade();
protected:
	bool m_fade_enable;
	f32 m_fade_dx;
	f32 m_fade_limit;
};

class C2DBitmap : public C2D, protected C2DFade
{
public:
	C2DBitmap();
public:
	void Load(f32 x, f32 y, zdb::CTexHandle* handle);
	void Load(f32 x, f32 y, f32 width, f32 height, zdb::CTexHandle* handle);

	void Draw(const CMatrix& transform, zdb::CTextureRelocMgr* reloc);
	void Draw(zdb::CCamera* camera);

	void TickFade();

	void MakePacket(zdb::CCamera* camera, zdb::CTextureRelocMgr* reloc, const CMatrix& transform);

	void Reset();

	bool GetTrans() const;

	void SetTrans(float translation);
	void SetPos(s32 x, s32 y, s32 width, s32 height);
	void SetPos(s32 x, s32 y);
	void SetUV(f32 u0, f32 v0, f32 u1, f32 v1);
	void SetColor(f32 red, f32 green, f32 blue);
private:
	s32 m_x;
	s32 m_y;

	f32 m_RGB[2][4];
	f32 m_NewUV[2][4];

	zdb::CTexHandle* m_pTexHandle;

	s32 m_iWidth;
	s32 m_iHeight;
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

class C2DFontEntry
{
private:
	char m_char;
	s32 m_offset;
	s32 m_width;
	s32 m_displaywidth;
	s32 m_xspacing;
	s32 m_top;
	s32 m_bottom;
	s32 m_baseline;
	s32 m_lKerning;
	s32 m_rKerning;
};

class C2DFont : public C2D
{
public:
	C2DFont();
private:
	std::vector<C2DFontEntry> m_charlist;
	// zdb::CTexHandle* m_pTexHandle;
	// zdb::CTexHandle* m_pGlowTexHandle;
	s32 m_displaytop;
	s32 m_displaybottom;
	s32 XPadding;
	f32 m_avgWidth;
	f32 m_opacity;
	f32 m_scale_factor;
};

class C2DMessage_Q : public C2D
{
private:
	C2DFont* m_font;

	C2DBitmap m_background1;
	C2DBitmap m_background2;

	f32 m_scale;
	s32 m_maxsize;

	s32 m_top;
	s32 m_left;

	s32 m_red;
	s32 m_blue;
	s32 m_green;

	f32 m_maxtrans;
	f32 m_transstep;

	s32 m_time;

	s32 m_lowestbottom;
	s32 m_spacing;

	bool m_centered;

	f32 m_maxlength;
	f32 m_TtySpeed;

	s32 m_cur_top;
	f32 m_moveTime;
	f32 m_target_top;

	bool m_descends;

	s32 m_XMargin;
	s32 m_YMargin;

	f32 m_displayTime;
	bool m_bEnabled;
	f32 m_Distance;
};