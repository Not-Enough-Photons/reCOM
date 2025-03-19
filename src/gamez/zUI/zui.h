#pragma once
#include <list>

#include "gamez/zTwoD/ztwod.h"
#include "gamez/zWeapon/zweapon.h"

class CUIVariable;
class CUIVariableSpec;
class CUIVarManager;

s32 ZuiInit();

enum UIVAR_LONGEVITY
{
	UIVL_DORMANT,
	UIVL_TEMPORARY,
	UIVL_PERMANENT,
	UIVL_PERSISTENT
};

class CZUI
{

};

class CUIVariable : public _zrdr
{
public:
	void Set(_zrdr* reader);

	char* m_varname;
	std::vector<void*> m_attached_items;
	UIVAR_LONGEVITY m_longevity;
};

class CUIVariableSpec
{
public:
	CUIVariableSpec(_zrdr* reader);

	char* m_name;
	_zrdr* m_array;
	CSTable m_stable;
	u32 m_type;
};

class CUIVarManager
{
public:
	CUIVariable* Add(const char* name, _zrdr* reader, UIVAR_LONGEVITY longevity);
};

class CDlgDesignModel
{
public:
	char* m_name;
	f32 m_elevation;
	f32 m_distance;
	bool m_usemodeluivar;
};

class CDesignDlgObj
{
	
};

class CDlgObjSpec
{
public:
	CUIVariableSpec* m_uivar;
};

class CTextSpec : public CDlgObjSpec
{
public:
	std::string m_caption;
	std::string m_font;
	bool m_hasFont;
	f32 m_scale;
	bool m_hCentered;
	PNT3D m_color;
};

class CImageSpec: public CDlgObjSpec
{
public:
	char* m_filename;
	IPNT2D m_scale;
	s32 m_xsize;
	s32 m_ysize;
	f32 m_pulse;
	bool m_doPulse;
};

class CButtonSpec : public CDlgObjSpec
{
public:
};

class CTtySpec : public CDlgObjSpec
{
public:
	s32 m_maxHeight;
	f32 m_pulseRate;
	f32 m_spacing;
	f32 m_interval;
	f32 m_maxLength;
	bool m_noCursor;
};

class CWrapSpec : public CDlgObjSpec
{
public:
	f32 m_width;
	s32 m_spacing;
	f32 m_height;
};

class CTickerSpec : public CTextSpec
{
public:
	f32 m_scrollSpeed;
	f32 m_width;
	f32 m_buffer;
};

class CHProgressBarSpec : public CImageSpec
{
public:
	bool m_filenameIsUiVar;
	std::string m_leadingEdgeNode;
};

class CCounterSpec : public CTextSpec
{
public:

};

class CClockSpec : public CTextSpec
{
public:

};

class CGameDlgDesign
{
public:
	void LoadFromRdr(_zrdr* reader);
	void LoadModels(_zrdr* reader);

	std::string m_filename;
	std::string m_font;
	
	bool m_useMpeg;

	std::vector<CSaferStr*> m_libs;
	std::vector<CDlgDesignModel*> m_models;
	std::vector<CDesignDlgObj*> m_dlgobjs;
	std::vector<CSaferStr*> m_animations;
};

extern CUIVarManager theUIVarManager;

