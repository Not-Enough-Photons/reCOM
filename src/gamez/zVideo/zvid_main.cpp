#include <GL/glew.h>
#include <SDL3/SDL.h>

#include "zvid.h"

#include "gamez/zReader/zrdr.h"
#include "gamez/zValve/zvalve.h"

_zvid_public zVid;
CValve* lodLevel = NULL;
CWindow* theWindow = NULL;

void zVid_Init(_zvid_mode mode)
{
	zVid.runTime = 0.0f;
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

	auto settings_rdr_file = zrdr_read("./data/zrdr/settings.rdr", NULL, 0);
	
	theWindow = new CWindow(settings_rdr_file);

	if (lodLevel == NULL)
	{
		lodLevel = CValve::Create("lodLevel", VALVE_TYPE::VTYPE_PERM);
	}

	if ((SDL_GetWindowFlags(theWindow->GetWindow()) & SDL_WINDOW_OPENGL) != 0)
	{
		zVid_Assert(glewInit() == GLEW_OK, LONG_MAX, __FILE__, __LINE__);
	}
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
	m_renderer = NULL;
}

CWindow::CWindow(CRdrFile* reader)
{
	auto tag = zrdr_findtag(reader, "settings");
	m_name = zrdr_findstring(tag, "name");
	zrdr_finduint(tag, "width", &m_width, 1);
	zrdr_finduint(tag, "height", &m_height, 1);

	auto window_flags_tag = zrdr_findtag(tag, "window_flags");
	
	u32 window_flags = 0;
	
	if (window_flags_tag)
	{
		for (u32 i = 1; i < window_flags_tag->array->integer; i++)
		{
			char* flag = window_flags_tag->array[i].string;

			if (SDL_strcasecmp(flag, "FULLSCREEN") == 0)
			{
				window_flags |= SDL_WINDOW_FULLSCREEN;
			}
			else if (SDL_strcasecmp(flag, "BORDERLESS") == 0)
			{
				window_flags |= SDL_WINDOW_BORDERLESS;
			}
			else if (SDL_strcasecmp(flag, "MINIMIZED") == 0)
			{
				window_flags |= SDL_WINDOW_MINIMIZED;
			}
			else if (SDL_strcasecmp(flag, "MAXIMIZED") == 0)
			{
				window_flags |= SDL_WINDOW_MAXIMIZED;
			}
		
			SDL_Log(window_flags_tag->array[i].string);
		}
	}
	
	m_window = SDL_CreateWindow(m_name, m_width, m_height, window_flags);

	zVid_Assert(m_window != NULL, LONG_MAX, __FILE__, __LINE__);

	m_renderer = SDL_CreateRenderer(m_window, NULL);

	if ((SDL_GetWindowFlags(m_window) & SDL_WINDOW_OPENGL) != 0)
	{
		SDL_GL_CreateContext(m_window);
	}
	
	zrdr_free(reader);
}

CWindow::CWindow(const char* name, u32 width, u32 height)
{
	m_name = zstrdup(name);
	m_width = width;
	m_height = height;
	
	m_window = SDL_CreateWindow(m_name, m_width, m_height, SDL_WINDOW_OPENGL);

	zVid_Assert(m_window != NULL, LONG_MAX, __FILE__, __LINE__);

	m_renderer = SDL_CreateRenderer(m_window, NULL);

	if ((SDL_GetWindowFlags(m_window) & SDL_WINDOW_OPENGL) != 0)
	{
		SDL_GL_CreateContext(m_window);
	}
}

SDL_Window* CWindow::GetWindow() const
{
	return m_window;
}

SDL_Renderer* CWindow::GetRenderer() const
{
	return m_renderer;
}