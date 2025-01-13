#include "zvid.h"

#include <GLFW/glfw3.h>

void zVid_Swap(bool doSwap)
{
	glfwSwapBuffers(theWindow->GetWindow());
}