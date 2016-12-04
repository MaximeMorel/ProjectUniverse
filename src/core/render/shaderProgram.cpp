////////////////////////////////////////////////////////////////////////////////
#include "shaderProgram.hpp"
////////////////////////////////////////////////////////////////////////////////
ShaderProgram::ShaderProgram(const std::string& name)
: Resource(name)
{
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgram::~ShaderProgram()
{
}
////////////////////////////////////////////////////////////////////////////////
uint32_t ShaderProgram::getProgId() const
{
    return m_shaderProgId;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::bind() const
{

}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::unbind() const
{

}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::addShader(ShaderPtr shader)
{

}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::link()
{

}
////////////////////////////////////////////////////////////////////////////////
