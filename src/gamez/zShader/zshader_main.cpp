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

void CShader::Link()
{
    s32 success = false;
    char infoLog[512];
    
    glAttachShader(m_ID, m_vertex);
    glAttachShader(m_ID, m_fragment);
    glLinkProgram(m_ID);
    
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        printf_s("E R R O R : Shader linking failed!\n%s", infoLog);
    }

    glDeleteShader(m_vertex);
    glDeleteShader(m_fragment);
}

void CShader::Create(const char* path, u32& shader, const u32& type)
{
    char* source = NULL;
    
    if (!path)
    {
        return;
    }

    std::fstream io(path);

    if (io.good())
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

    s32 success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf_s("E R R O R (%s) : Shader compilation failed!\n%s", path, infoLog);
    }
}

void CShader::Bind()
{
    glUseProgram(m_ID);
}

void CShader::Unbind()
{
    
}