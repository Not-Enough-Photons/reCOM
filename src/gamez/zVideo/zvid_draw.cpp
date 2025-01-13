#include "zvid.h"

#include <GLFW/glfw3.h>

void zVid_Swap(bool doSwap)
{
	glfwSwapBuffers(theWindow->GetWindow());
}

void zVid_ClearColor(f32 red, f32 green, f32 blue)
{
	glClearColor(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
}