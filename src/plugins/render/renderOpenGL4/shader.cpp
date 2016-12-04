////////////////////////////////////////////////////////////////////////////////
#include "shader.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
ShaderGL4::ShaderTypeMapping::ShaderTypeMapping()
{
    m_mapping[Type::VERTEX_SHADER] = GL_VERTEX_SHADER;
    m_mapping[Type::TESS_CONTROL_SHADER] = GL_TESS_CONTROL_SHADER;
    m_mapping[Type::TESS_EVALUATION_SHADER] = GL_TESS_EVALUATION_SHADER;
    m_mapping[Type::GEOMETRY_SHADER] = GL_GEOMETRY_SHADER;
    m_mapping[Type::FRAGMENT_SHADER] = GL_FRAGMENT_SHADER;
    m_mapping[Type::COMPUTE_SHADER] = GL_COMPUTE_SHADER;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t ShaderGL4::ShaderTypeMapping::get(Type t)
{
    return m_mapping[t];
}
////////////////////////////////////////////////////////////////////////////////
ShaderGL4::ShaderGL4(const std::string& name, Type t)
: Shader(name, t)
{
    m_shaderId = glCreateShader(m_shaderTypeMapping.get(t));
    const GLchar* src = "#version 450 core \
                         out vec4 color; \
                         void main(void) \
                         { \
                             color = vec4(0.0, 0.8, 1.0, 1.0); \
                         }";
    glShaderSource(m_shaderId, 1, &src, nullptr);
    glCompileShader(m_shaderId);
}
////////////////////////////////////////////////////////////////////////////////
ShaderGL4::~ShaderGL4()
{
    glDeleteShader(m_shaderId);
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr ShaderGL4::create(const std::string& name, Type t)
{
    return std::shared_ptr<ShaderGL4>(new ShaderGL4(name, t));
}
////////////////////////////////////////////////////////////////////////////////
uint32_t ShaderGL4::getId() const
{
    return m_shaderId;
}
////////////////////////////////////////////////////////////////////////////////
