#include <GL/glew.h>
#include <SDL3/SDL_timer.h>

#include "zvid.h"

f32 lastRenderTime = 0.0f;
f32 curRenderTime = 0.0f;

void zVid_Swap(bool doSwap)
{
	lastRenderTime = 0.0f;
	curRenderTime = 0.0f;

	lastRenderTime = SDL_GetTicks();
	SDL_GL_SwapWindow(theWindow->GetWindow());
	curRenderTime = SDL_GetTicks();

	zVid.frameTime = (curRenderTime - lastRenderTime) * zSys.timerScale;
	zVid.frameRate = 1.0f / zVid.frameTime + 0.5f;
	zVid.runTime += zVid.frameTime;
	zVid.frameNumber++;
}

void zVid_ClearColor(f32 red, f32 green, f32 blue)
{
	glClearColor(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}