#pragma once
#include "gamez/zUI/zui.h"

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
	float m_curpos;
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
	float m_fadetime;
	float m_fadetotal;
	float m_faderate;
	float m_brightness;
	float m_min_brightness;
};