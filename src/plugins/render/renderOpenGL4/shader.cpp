////////////////////////////////////////////////////////////////////////////////
#include "shader.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
ShaderGL4::ShaderGL4(const std::string& name)
: Shader(name)
{
    m_shaderId = glCreateShader(GL_VERTEX_SHADER);
}
////////////////////////////////////////////////////////////////////////////////
ShaderGL4::~ShaderGL4()
{
    glDeleteShader(m_shaderId);
}
////////////////////////////////////////////////////////////////////////////////
GLuint ShaderGL4::getId() const
{
    return m_shaderId;
}
////////////////////////////////////////////////////////////////////////////////