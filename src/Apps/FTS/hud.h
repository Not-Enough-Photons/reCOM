#pragma once
#include "gamez/zUI/zui.h"

class CMissionCam;

extern CHUD* theHUD;

enum HUD_MODE
{
	ZOOMIN,
	ZOOMOUT
};

class CLetterBox : C2D
{
public:
	enum SLIDE_DIRECTION
	{
		SLIDE_NONE,
		SLIDE_IN,
		SLIDE_OUT
	};
private:
	C2DBitmap m_bitmap[2];
	SLIDE_DIRECTION m_slidedir;
	f32 m_curpos;
};

class CFader : C2DBitmap
{
public:
	enum FADE_DIRECTION
	{
		IN,
		OUT,
		FADE
	};
private:
	FADE_DIRECTION m_fadedir;
	f32 m_fadetime;
	f32 m_fadetotal;
	f32 m_faderate;
	f32 m_brightness;
	f32 m_min_brightness;
};

class CLensFlareSaturate : public C2DBitmap
{
private:
	bool m_Active;

	f32 m_MinDot;
	f32 m_DotScalar;
	bool m_On;

	CPnt3D m_CameraPos;
	zdb::DiIntersect m_CameraLightDI;
	bool m_CameraLightDIValid;

	bool m_GlareActive;
	f32 m_GlareBrightness;
	f32 m_GoalGlareBrightness;
	f32 m_MaxGlareBrightness;
	
	bool m_LensFlareActive;
	zdb::CNode* m_LensFlareNode;
	f32 m_LensFlareDistance;
	f32 m_MinLensFlareOpacity;
	f32 m_LensFlareOpacityRange;
	f32 m_MinLensFlareScale;
	f32 m_LensFlareScaleRange;
	zdb::CNode* m_LightNode;
	CPnt3D m_LightPos;
	f32 m_MinLightNodeOpacity;
	f32 m_LightNodeOpacityRange;
};

class CHudBrightText : public C2DString {};

class CHudCompassAnchor
{
private:
	C2DBitmapPoly m_icon;
	C2DString m_string;

	f32 m_width;
	f32 m_height;

	zdb::CTexHandle* m_htex;
	zdb::CTexture* m_texture;
};

class MapCompass
{
private:
	f32 m_scale;

	zdb::CTexture* m_newcompasstex;

	zdb::CTexHandle* m_anchor_img[33];
	CPnt3D m_anchor_clr[33];

	f32 m_tex_width;
	f32 m_tex_height;

	f32 m_compasstopx;
	f32 m_compasstopy;
	f32 m_compassbotx;
	f32 m_compassboty;
	f32 m_compasscenterx;
	f32 m_compasscentery;

	C2DBitmapPoly m_poly;

	C2D m_anchor_head;

	C2DBitmap m_fov;
	zdb::CTexture m_fovtex;

	CHudCompassAnchor m_compass_anchors[33];
	CHudCompassAnchor m_compass_arrows[33];
};

class CZNewHudMap : public C2D
{
private:
	std::list<void*> m_itemlist;

	CZSealBody* m_viewer;

	f32 m_screenx1;
	f32 m_screeny1;
	f32 m_screenx2;
	f32 m_screeny2;

	CPnt3D m_world1;
	CPnt3D m_world2;
	CPnt3D m_world3;
	CPnt3D m_world4;

	f32 m_screencenterx;
	f32 m_screencentery;
	f32 m_width;
	f32 m_worldcenterx;
	f32 m_worldcentery;
	f32 m_scale;

	f32 m_radar_distance;

	CMatrix m_matrix;

	C2DBitmapPoly m_background;
	C2DBitmapPoly m_oldbackground;

	zdb::CTexture* m_backtex;
	zdb::CTexture* m_oldbacktex;
	// CCircleClip* m_circleclipper;

	f32 m_centerx;
	f32 m_centery;

	bool m_isFullScreen;

	MENU_STATE m_oldmenustate;

	// CZObjectiveList m_objectivelist;
	CHUD* m_parent;

	CSnd* m_zoominsound;
	CSnd* m_zoomoutsound;
};

class CWeaponSel : public C2D
{
private:
	CHUD* m_parent;

	C2DBitmap m_weaponicon[4];
	s32 m_weaponnum;
	C2DBitmap m_weaponselbkrnd;
	C2DBitmap m_selectionback[4];
	C2DBitmapPoly m_arrow[2];

	CHudBrightText m_hotswapL1text;
	CHudBrightText m_hotswapL2text;
	CHudBrightText m_weaponname;
	C2DString m_weapondescription;

	C2DString m_ammotype;
	CHudBrightText m_ammocount;
	CHudBrightText m_magcount;

	zdb::CTexHandle* m_weaponselbkrndtex;
	zdb::CTexHandle* m_weapontex[4];
	zdb::CTexHandle* m_selectionbacktex;
	zdb::CTexture* m_arrowtex;

	C2DFont* m_myfont;

	s32 m_current_item;
	s32 m_openstate;

	f32 m_nameoffsetx;
	f32 m_nameoffsety;
	f32 m_iconoffsetx;
	f32 m_iconoffsety;
	f32 m_menugoalx;
	f32 m_menugoaly;
	f32 m_menuposx[4];
	f32 m_menuposy[4];
	f32 m_menucentery;
	f32 m_menustartx;
	f32 m_curheight;
	f32 m_goalheight;

	f32 m_curtrans[2];
	f32 m_goaltrans[2];

	f32 m_curcolor;

	u8 m_incCurcolor;

	f32 m_arrowcolor;
	u8 m_arrowincrement;

	CSnd* m_selectsound;
	CSnd* m_scrollupsound;
	CSnd* m_scrolldownsound;
	s32 m_cursound;
};

class CInGameWeaponSel : public C2D
{
public:
	void HudTick(f32 delta);
	void GetPrevItem(s32 param_1);
	void Clear();
	void Init(zdb::CWorld* world);
	void SelectWeapon();
	void SelectEquipment();
	bool CanSelectWeapon(s32 index) const;
private:
	CHUD* m_parent;

	C2DBitmap m_weaponicon[4];
	C2DString m_selectedtext[3];

	s32 m_selected[4];
	s32 m_icon_selected[4];

	C2DBitmap m_weaponselbkrnd;
	C2DBitmap m_selectionback[4];
	C2DBitmapPoly m_arrow[2];

	C2DString m_weaponname;
	C2DString m_weapondescription;
	C2DString m_ammotype;
	C2DString m_ammocount;
	C2DString m_magcount;
	C2DString m_weaponselectedname[6];
	C2DString m_weaponselectedtitle;
	zdb::CTexHandle* m_weaponselbkrndtex;
	zdb::CTexHandle* m_weapontex[4];
	zdb::CTexHandle* m_selectionbacktex[4];
	zdb::CTexture* m_arrowtex;

	C2DFont* m_myfont;
	s32 m_current_item;
	s32 m_openstate;

	f32 m_nameoffsetx;
	f32 m_nameoffsety;
	f32 m_iconoffsetx;
	f32 m_iconoffsety;
	f32 m_menugoalx;
	f32 m_menugoaly;
	f32 m_menuposx[4];
	f32 m_menuposy[4];
	f32 m_menucentery;
	f32 m_menustartx;
	f32 m_curheight;
	f32 m_goalheight;

	f32 m_curtrans[2];
	f32 m_goaltrans[2];

	f32 m_curcolor;
	u8 m_incCurcolor;

	f32 m_arrowcolor;
	u8 m_arrowincrement;

	CSnd* m_selectsound;
	CSnd* m_scrollupsound;
	CSnd* m_scrolldownsound;
	s32 m_cursound;

	EQUIP_ITEM m_selected_item_index[6];
};

class CTeamNames : public C2D
{
private:
	PNT3D m_allycolor[4];
	PNT3D m_allycolorgoal[4];
	CZSealBody* m_ally[4];
	CHudBrightText m_teamname[4];
	C2DString m_order[4];
	f32 m_arrOrderFadeTimes[4];

	C2DFont* m_myfont;

	f32 m_increment;

	C2DBitmap m_background;
	C2DBitmap m_healthdot[4];
};

class OrdersMenu
{
private:
	bool m_no_menu;
	bool m_was_PTT;

	f32 m_circle_down_time;
	f32 m_circle_down_max;
	f32 m_time_since_last_chat;

	bool m_has_scroll_sound;
	bool m_has_select_sound;
	bool m_has_complete_sound;

	C2DOrderItem* m_team_text;
	C2DOrderItem* m_cmd_text;
	C2DOrderItem* m_aux_text;

	f32 m_fade_time;

	bool m_shutdown;

	s32 m_size[3];
	s32 m_selection[3];

	FIRETEAM m_selected_team;
	void* m_submenu;
	void* m_command;

	C2D m_list;

	s32 m_topx;
	s32 m_topy;
	s32 m_botx;
	s32 m_boty;
	s32 m_selected_row;
	s32 m_selected_col;

	C2DFont* m_ordersfont;

	zdb::CTexHandle* m_team_active_tex;
	zdb::CTexHandle* m_team_inactive_tex;
	zdb::CTexHandle* m_cmd_active_tex;
	zdb::CTexHandle* m_cmd_inactive_tex;
	zdb::CTexHandle* m_aux_active_tex;
	zdb::CTexHandle* m_aux_inactive_tex;
	zdb::CTexHandle* m_arrow_tex;

	f32 m_order_speed;
	f32 m_item_width;
	f32 m_item_height;

	IPNT2D m_text_offset;

	// CSaferStr m_upSound;
	// CSaferStr m_selectSound;
	// CSaferStr m_completeSound;

	C2DString m_ExplanationText;
	C2DBitmap m_ExplanationBackgroundLeft;
	C2DBitmap m_ExplanationBackgroundRight;
	C2DBitmap m_ExplanationBackgroundCenterLeft;
	C2DBitmap m_ExplanationBackgroundCenterRight;
};

class CTeamMateNames : public C2D
{
private:
	C2DString m_teamMateNames[15];
	f32 xMargin;
};

class CZPauseTest : public C2D
{
private:
	C2DString m_selections[5];
	C2DBitmap m_background;

	s32 m_curselection;

	C2DFont* m_font;

	bool m_on;
	bool m_wason;

	f32 m_curcolor;
	f32 m_inc;

	MENU_STATE m_oldmenustate;

	s32 m_numselections;

	CSnd* m_selectsound;
	CSnd* m_scrollupsound;
	CSnd* m_scrolldownsound;
};

class BitmapReticule : public C2D
{
private:
	CHUD* m_parent;

	C2DBitmap m_bitmap;
	C2DBitmap m_grenadebitmap;
	C2DBitmap m_grenadebitmap2;
	C2DBitmap m_miss_x;
	C2DBitmapPoly m_grenadeactive[2];
	C2DBitmapPoly m_grenadeback[2];
	C2DBitmapPoly m_scopepoly[4];
	C2DBitmapPoly m_threatdirpoly[8];
	C2DBitmapPoly m_floatingreticule[4];
	C2DBitmap m_nvgrange;
	C2DBitmapPoly m_nvglens[4];

	bool m_nvgenabled;

	C2DString m_lase_update;
	f32 m_prev_lase;
	char m_lase_str[32];
	bool m_target_verified;

	C2DString m_detonation_update;
	char m_detonation_str[32];
	bool m_detonation_verified;
	f32 m_prev_deton;

	C2DBitmap m_timer_IMAGE;
	C2DBitmap m_timer_BKGRD;

	f32* m_pCurval;
	f32 m_maxval;
	f32 m_maxval_frac;
	bool m_bIncrTimer;

	f32 m_posx;
	f32 m_posy;
	f32 m_retsize;
	s32 m_rettype;

	zdb::CTexHandle* m_reticuleTex[10];
	zdb::CTexHandle* m_floatingreticuleTex[10];
	zdb::CTexHandle* m_grenadebartex_full;
	zdb::CTexHandle* m_accuracyxtex;
	zdb::CTexHandle* m_threatdirTex;

	bool m_error;

	f32 m_minsize;
	f32 m_maxsize;
	f32 m_rettexsizex;
	f32 m_rettexsizey;
	f32 m_rettexsizex2;
	f32 m_rettexsizey2;
	f32 m_threattexsizex;
	f32 m_threattexsizey;

	C2DString m_enemy_name;
};

class CZActionBitmap : public C2DBitmap
{
private:
	zdb::CTexHandle* m_canClimbTexture;
	zdb::CTexHandle* m_pttTexture;
	zdb::CTexHandle* m_canDropMPBomb;
	zdb::CTexHandle* m_canKnifeTexture;
	zdb::CTexHandle* m_canPickupTexture;
	zdb::CTexHandle* m_canRestrainTexture;
	zdb::CTexHandle* m_canCQBTexture;
	zdb::CTexHandle* m_canCarryBodyTexture;
	zdb::CTexHandle* m_actionXTexture;
	CHUD* m_parent;
};

class CZStaticRadioBitmap : public C2DBitmap
{
private:
	zdb::CTexHandle* m_pRadioOffTexture;
	zdb::CTexHandle* m_pRadioChannelTeamTexture;
	zdb::CTexHandle* m_pRadioChannelOffenseTexture;
	zdb::CTexHandle* m_pRadioChannelDefenseTexture;
	zdb::CTexHandle* m_pRadioChannelDeadTexture;
	CHUD* m_pParent;
};

class CZDynamicRadioBitmap : public C2DBitmap
{
private:
	zdb::CTexHandle* m_pRadioChannelInUseTexture;
	zdb::CTexHandle* m_pRadioChannelCanTalkTexture;
	CHUD* m_pParent;
};

class CZHudMissionCams : public C2D
{
private:
	CMissionCam* m_currentcam;

	CZAnim* m_animhandle;

	C2DString m_letterboxobjectivename;
	C2DString m_letterboxobjectivedescription[3];
	C2DBitmap m_crossbitmap;
	C2DString m_crosstext;
	zdb::CTexHandle* m_crosstexture;

	s32 m_pause_for_frame;

	MENU_STATE m_lastmenustate;
};

/// <summary>
/// HUD class that displays your health, squad, ammo, etc.
/// </summary>
class CHUD
{
	// Nothing ever happens.
public:
	CHUD();

	void Init(zdb::CWorld* world);
private:
	// CDynTexList m_dyntexlist;

	s32 m_hudrettype;
	bool m_usehudret;
	bool m_hudretchanged;

	zdb::CTexture* reticuletexture;
	zdb::CTexHandle* m_firemodetex;

	f32 m_weapontopx;
	f32 m_weapontopy;
	f32 m_weaponbotx;
	f32 m_weaponboty;

	C2DBitmap weapon;

	C2DString m_firemodename;
	C2DBitmap m_firemode;
	CPlainBmp m_WeaponBackground;

	f32 m_compasstopx;
	f32 m_compasstopy;
	f32 m_compassbotx;
	f32 m_compassboty;
	f32 m_compasscenterx;
	f32 m_compasscentery;

	C2DFont* m_myfont;

	s32 m_curweapon;
	s32 m_curseal;

	f32 pointpos[4][2];
	f32 pointvel[4][2];

	CHudBrightText m_ammocount;
	CHudBrightText m_magscount;
	C2DString m_ammotype;
	CHudBrightText m_weaponname;
	C2DString m_zoomleveltext;

	f32 m_messageTime;
	C2DString m_message;
	C2DString m_perfstats[30];
	CWeaponSel m_weaponsel;
	CInGameWeaponSel m_ingameweaponsel;

	C2DString m_timertext;
	C2DString m_rangetext;

	MapCompass m_mapcompass;
	CZNewHudMap m_newmap;
	PoseBitmap m_poseBitmap;
	BitmapReticule m_bitmapReticule;
	OrdersMenu m_ordermenu;
	CTeamNames m_teamnames;
	CZActionBitmap m_actionbitmap;
	CTeamMateNames m_teamMateNames;
	CZStaticRadioBitmap m_static_radio_bitmap;
	CZDynamicRadioBitmap m_dynamic_radio_bitmap;
	CZPauseTest m_pausetest;

	C2DString m_num_connect;
	C2DString m_piggyback_text1;
	C2DString m_piggyback_text2;
	C2DString m_piggyback_text3;
	CLetterBox m_letterbox;
	CFader m_bmpFade;

	// std::vector<CFlashFX*> m_FlashFXVector;
	CLensFlareSaturate m_LensFlareFade;

	CZHudMissionCams m_missioncams;

	C2D m_phase[3];

	HUD_MODE m_hudmode;

	bool m_ison;
};

class CCompassAnchor
{

};