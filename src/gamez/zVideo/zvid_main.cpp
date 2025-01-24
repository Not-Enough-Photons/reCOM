#include <GL/glew.h>
#include <SDL3/SDL.h>

#include "zvid.h"

#include "gamez/zValve/zvalve.h"

_zvid_public zVid;
CValve* lodLevel = NULL;
CWindow* theWindow = NULL;

void zVid_Init(_zvid_mode mode)
{
	zVid_Assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO), LONG_MAX, __FILE__, __LINE__);

	zVid.runTime = 0.0f;
	zVid.renderWidth = 640;
	zVid.renderHeight = 448;
	zVid.renderBuf = NULL;
	zVid.ztest_on = GL_DEPTH_TEST;
	zVid.ztest_off = GL_DEPTH_TEST;
	zVid.doMpeg224 = false;
	zVid.minZ = 10.0f;
	zVid.pcrtcDo = false;
	zVid.maxZ = 65535.0f;
	zVid.aspect[0] = 1.0f;
	zVid.aspect[1] = 1.0f;
	zVid.displayBuf = NULL;
	zvid_SetVideoMode(mode);

	theWindow = new CWindow("fts", zVid.renderWidth, zVid.renderHeight);

	if (lodLevel == NULL)
	{
		lodLevel = CValve::Create("lodLevel", VALVE_TYPE::PERM);
	}

	zVid_Assert(glewInit() == GLEW_OK, LONG_MAX, __FILE__, __LINE__);
}

void zVid_Open()
{
}

void zvid_SetVideoMode(_zvid_mode mode)
{
	zVid.vidMode = mode;
	zVid.videoMode = mode;
}

CWindow::CWindow()
{
	m_name = NULL;
	m_width = 0;
	m_height = 0;
	m_window = NULL;
}

CWindow::CWindow(const char* name, u32 width, u32 height)
{
	m_name = zstrdup(name);
	m_width = width;
	m_height = height;

	m_window = SDL_CreateWindow(m_name, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED);

	zVid_Assert(m_window != NULL, LONG_MAX, __FILE__, __LINE__);

	SDL_GL_CreateContext(m_window);
}

SDL_Window* CWindow::GetWindow() const
{
	return m_window;
}