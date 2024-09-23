#include "zmath_main.h"

namespace zdb
{
	C2DLine::C2DLine()
	{
		m_p1 = { 0.0, 0.0 };
		m_p2 = { 0.0, 0.0 };
	}

	C2DLine::C2DLine(float x1, float y1, float x2, float y2)
	{
		m_p1 = { x1, y1 };
		m_p2 = { x2, y2 };
	}

	C2DLine::C2DLine(Vector2 p1, Vector2 p2)
	{
		m_p1 = p1;
		m_p2 = p2;
	}

	C2DLine::C2DLine
}