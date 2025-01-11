#include "zrender.h"

CPipe thePipe;

CPipe::CPipe()
{
	m_wireframe = false;
	m_terrain = false;
	m_alpha.m_visualList = zmalloc(22400);
	m_alpha.m_next = m_alpha.m_visualList;
	m_delayedNodeNum = 0;
	
	m_drawDI = false;
	m_drawBBox = false;
	m_drawNormal = false;
	m_reticuleDraw = false;
	m_LODFilter = false;

	m_opacity_stack = static_cast<f32*>(zcalloc(4, 32));
	*m_opacity_stack = 1.0f;
	m_opacity_stack_size = 32;
	m_opacity_stack_index = 0;

	m_DelayedNodes.reserve(48);
	
	m_texIntIdx = 0;
	m_texLoadIdx = 0;
}