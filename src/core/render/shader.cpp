////////////////////////////////////////////////////////////////////////////////
#include "shader.hpp"
////////////////////////////////////////////////////////////////////////////////
Shader::Shader(const std::string& name, Type t)
: Resource(name)
{
}
////////////////////////////////////////////////////////////////////////////////
Shader::~Shader()
{
}
////////////////////////////////////////////////////////////////////////////////
uint32_t Shader::getShaderId() const
{
    return m_shaderId;
}
////////////////////////////////////////////////////////////////////////////////
