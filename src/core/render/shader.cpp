////////////////////////////////////////////////////////////////////////////////
#include "shader.hpp"
////////////////////////////////////////////////////////////////////////////////
Shader::Shader(const std::string& name)
: Resource(name)
{
}
////////////////////////////////////////////////////////////////////////////////
Shader::~Shader()
{
}
////////////////////////////////////////////////////////////////////////////////
unsigned int Shader::getId() const
{
    return m_shaderId;
}
////////////////////////////////////////////////////////////////////////////////