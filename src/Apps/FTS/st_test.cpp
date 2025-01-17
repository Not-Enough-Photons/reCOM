#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    0.0f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f
};

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    if (m_bTestLoadReaders)
    {
        TestLoadReaders(path);
    }

    shader.Init();
    
    shader.Create(".../data/common/shaders/unlit_vertex.shader", shader.m_vertex, GL_VERTEX_SHADER);
    shader.Create(".../data/common/shaders/unlit_fragment.shader", shader.m_fragment, GL_FRAGMENT_SHADER);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

void CTestState::Tick(f32 dT)
{
    glfwPollEvents();
    zVid_ClearColor(0.0f, 0.0f, 0.0f);
    glUseProgram(shader.m_ID);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    zVid_Swap(false);
}

void CTestState::TestLoadReaders(const char* path)
{
    CRdrArchive::AddArchive(path, NULL);
    CRdrArchive::OpenAll();
    _zrdr* reader = CRdrArchive::FindRdr("motion.rdr");
    CRdrArchive::CloseAll();
}
