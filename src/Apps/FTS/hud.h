#pragma once
#include "gamez/zUI/zui.h"

class CLetterBox : C2D
{
public:
	enum SLIDE_DIRECTION
	{
		UP,
		DOWN
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
		OUT
	};
private:
	FADE_DIRECTION m_fadedir;
	float m_fadetime;
	float m_fadetotal;
	float m_faderate;
	float m_brightness;
	float m_min_brightness;
};