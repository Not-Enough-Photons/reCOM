#include "gamez/zSystem/zsys.h"

_zsys_public zSys;
bool postinit = false;

CWindow::CWindow()
{
	m_name = NULL;
	m_width = 0;
	m_height = 0;
}

CWindow::CWindow(const char* name, u32 width, u32 height)
{
	m_name = zstrdup(name);
	m_width = width;
	m_height = height;

	m_window = glfwCreateWindow(m_width, m_height, name, NULL, NULL);

	zVid_Assert(m_window != NULL, LONG_MAX, __FILE__, __LINE__);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(m_window);
}

GLFWwindow* CWindow::GetWindow() const
{
	return m_window;
}