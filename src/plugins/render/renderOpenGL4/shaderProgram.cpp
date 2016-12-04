////////////////////////////////////////////////////////////////////////////////
#include "shaderProgram.hpp"
#include <GL/glew.h>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL4::ShaderProgramGL4(const std::string& name)
: ShaderProgram(name)
{
    m_shaderProgId = glCreateProgram();
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL4::~ShaderProgramGL4()
{
    // attached shaders are automatically detached
    glDeleteProgram(m_shaderProgId);
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr ShaderProgramGL4::create(const std::string& name)
{
    return std::shared_ptr<ShaderProgramGL4>(new ShaderProgramGL4(name));
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::bind() const
{
    glUseProgram(m_shaderProgId);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::unbind() const
{
    glUseProgram(0);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::addShader(ShaderPtr shader)
{
    GLenum err = glGetError();
    while (err != GL_NO_ERROR)
        err = glGetError();
    glAttachShader(m_shaderProgId, shader->getShaderId());
    err = glGetError();
    if (err == GL_NO_ERROR)
        m_shaders.push_back(shader);
    else
        std::cout << "addShader fail: " << err << "\n";
        //log().log() << "addShader fail: " << err << "\n";
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::link()
{
    glLinkProgram(m_shaderProgId);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
