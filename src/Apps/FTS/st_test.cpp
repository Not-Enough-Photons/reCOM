#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gamez/zEntity/zentity.h"
#include "gamez/zFTS/fts_state.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zRender/zShader/zshader.h"
#include "gamez/zVideo/zvid.h"

const char* path = "D:/RUN/READERC.ZAR";

u32 vao;
u32 vbo;

CShader shader;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    const char* rdrpath = "C:/Users/adamdev.NOTENOUGHPHOTON/Desktop/reader.rdr";
    _zrdr* test = zrdr_read(rdrpath, NULL, 1);
    return true;
}

void CTestState::Tick(f32 dT)
{

}
