#include <GL/glew.h>

#include "gamez/zEntity/zentity.h"
#include "gamez/zFTS/fts_state.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zRender/zShader/zshader.h"
#include "gamez/zVideo/zvid.h"
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
    const char* path = "D:/run/readerc.zar";
    CRdrArchive::AddArchive(path, NULL);
    CRdrArchive::OpenAll();
    CCharacterType::Open("character.rdr");
    // CValve::Open("global_valves.rdr", VALVE_TYPE::PERM);
    CRdrArchive::CloseAll();
    return true;
}

void CTestState::Tick(f32 dT)
{

}
