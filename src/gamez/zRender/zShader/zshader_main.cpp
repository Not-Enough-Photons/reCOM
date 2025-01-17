#include <sstream>
#include <fstream>

#include <GL/glew.h>

#include "zshader.h"

CShader::CShader()
{
    m_ID = 0;
    
    m_vertex = 0;
    m_fragment = 0;
}

void CShader::Init()
{
    m_ID = glCreateProgram();
}

void CShader::Create(const char* path, u32& shader, const u32& type)
{
    char* source = NULL;
    
    if (!path)
    {
        return;
    }

    std::fstream io(path);

    if (io)
    {
        std::stringstream buffer;

        buffer << io.rdbuf();
        io.close();
        source = zstrdup(buffer.str().c_str());
        buffer.flush();
    }
    else
    {
        return;
    }

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glAttachShader(m_ID, shader);
    glDeleteShader(shader);
}

void CShader::Bind()
{
    glUseProgram(m_ID);
}

void CShader::Unbind()
{
    
}