#pragma once
#include <SDL3/SDL.h>

#include "gamez/zAnim/zanim.h"
#include "gamez/zCamera/zcam.h"
#include "gamez/zInput/zinput.h"
#include "gamez/zSystem/zsys.h"

class C2D;
class C2DFont;
class CUIVariable;

namespace zdb
{
	class CTexture;
	class CTextureRelocMgr;
	class CTexHandle;
}

enum tag_string_type
{
	STRING_PLAIN,
	STRING_GLOWY,
	STRING_NUM_TYPES
};

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

	void Load(f32 x, f32 y, zdb::CTexHandle* handle);
	void Load(f32 x, f32 y, f32 width, f32 height, zdb::CTexHandle* handle);

	void Draw(const CMatrix& transform, zdb::CTextureRelocMgr* reloc);
	void Draw(zdb::CCamera* camera);

	void TickFade();

	void MakePacket(zdb::CCamera* camera, zdb::CTextureRelocMgr* reloc, const CMatrix& transform);

	void Reset();

	bool GetTrans() const;

	void SetTrans(float transparency);
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
	SDL_Texture* m_sdlTexture;
	SDL_FRect m_rect;

	s32 m_iWidth;
	s32 m_iHeight;
};

class C2DPoly : public C2D
{
public:
	C2DPoly();
};

class C2DBitmapPoly : public C2D, protected C2DFade
{
	s32 x1;
	s32 x2;
	s32 y1;
	s32 y2;

	C2DPoly m_tris[2];
	zdb::CTexture* m_texture;
};

class CPlainBmp : public C2D
{
public:
	CPlainBmp() {}
};

class C2DString : public C2D
{
public:
	C2DString();

	void AddCharacter(char character);

	void SetString(const char* string);

	void Draw(zdb::CCamera* camera);
	
	void Load(const char* message, C2DFont* font, s32 x, s32 y, s32 width, s32 height);
	void Load(const char* message, C2DFont* font, s32 x, s32 y);
	void Load(f32 scale, const char* message, C2DFont* font, s32 x, s32 y);
	
	C2DFont* m_font;

	char* m_string;
	s32 m_stringlen_max;
	s32 m_numChars;

	char* m_Ustring;
	s32 m_Ustringlen_max;
	s32 m_numUChars;

	f32 m_charwidth;
	f32 m_charheight;
	f32 m_length;
	f32 m_height;
	f32 m_scale;
	
	s32 m_numLines;

	CPnt4D m_color;

	s32 m_revnum;

	f32 m_fadeTime;
	f32 m_fadeMax;
	f32 m_fadeMin;

	tag_string_type m_Type;

	bool m_isCentered;
	
	u32 m_firstCharPos;
	s32 m_shortLength;

	f32 m_elapsedTime;

	IPNT2D m_pos;
};

class C2DMessageString : public C2D
{

};

class C2DOrderItem : public C2DBitmap
{
	f32 m_width;
	f32 m_height;
	f32 m_speed;

	IPNT3D m_text_offset;

	s32 m_target_x;
	s32 m_target_y;
	s32 m_target_x2;
	s32 m_target_y2;
	s32 m_state2;
	s32 m_state;
	f32 m_time;

	C2DString m_text;
	C2DBitmap m_glowing_background;
	C2DBitmap m_arrow;

	zdb::CTexHandle* m_active_tex;
	zdb::CTexHandle* m_inactive_tex;
	zdb::CTexHandle* m_arrow_tex;

	bool m_glow;
	f32 m_trans_step;
	f32 m_blinkTime;
	char* m_Explanation;
	bool m_bArrow;
};

class PoseBitmap : public C2DBitmap
{
	s32 m_curpose;

	zdb::CTexture* m_posetex[3];

	f32 m_posx;
	f32 m_posy;
	bool m_error;

	C2DString m_text;
	f32 m_textposx;
	f32 m_textposy;

	C2DFont* m_myfont;
	f32 m_trans;
};

class C2DFontEntry
{
public:
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
	void Load(CRdrFile* font, const char* name);

	C2DFontEntry* GetEntry(char character);
	
	std::vector<C2DFontEntry*> m_charlist;
	zdb::CTexHandle* m_pTexHandle;
	zdb::CTexHandle* m_pGlowTexHandle;
	s32 m_displaytop;
	s32 m_displaybottom;
	s32 XPadding;
	f32 m_avgWidth;
	f32 m_opacity;
	f32 m_scale_factor;
};

class C2DMessage_Q : public C2D
{
public:
	C2DMessage_Q();

	void Init(C2DFont* font, CRdrFile* reader);
	
	void ScrollUp();
	void SetBkgColor(f32 r, f32 g, f32 b);
	
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

class C3StateButton : public C2D
{
public:
	char* _szCaption;
	C2DString _strCaption;
	s32 _iTextX;
	s32 _iTextY;
	bool _bCaptionCentered;
};

class C2DButton : public C3StateButton
{
public:
	struct ButtonState
	{
		CSaferStr _TexName;
		zdb::CTexHandle* _Texture;
		f32 _iGlowStart;
		f32 _iGlowEnd;
		bool _bGlowy;
		f32 _fPulseTime;
		f32 _fGlowTime;
		CPnt3D _pntTextColor;
		f32 _fScale;
	};

	ButtonState _PressedState;
	ButtonState _ActiveState;
	ButtonState _NormalState;
	ButtonState _DisabledState;

	CPlainBmp _bmp;

	f32 _fWidth;
	f32 _fHeight;

	C2DFont* m_alternateFont;

	f32 _fPressedTime;
};