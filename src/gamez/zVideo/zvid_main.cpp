#include <GL/glew.h>
#include <SDL3/SDL.h>

#include "zvid.h"

#include "gamez/zReader/zrdr.h"
#include "gamez/zValve/zvalve.h"

_zvid_public zVid;
CValve* lodLevel = NULL;

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
	zVid.frameRate = 144.0f;
	zVid.hblnkRate = 15750.0f;
	zvid_SetVideoMode(mode);

	zVid_CreateWindow();

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