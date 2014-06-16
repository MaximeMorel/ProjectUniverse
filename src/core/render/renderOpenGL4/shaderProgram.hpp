#ifndef __SHADERPROGRAM_OPENGL4_HPP__
#define __SHADERPROGRAM_OPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/shaderProgram.hpp"
#include "shader.hpp"
#include <string>
////////////////////////////////////////////////////////////////////////////////
class ShaderProgramGL4 : public ShaderProgram
{
public:
    ShaderProgramGL4(const std::string& name);

    virtual ~ShaderProgramGL4() override;

    //virtual void addShader(Shader* shader) override;

private:
    unsigned int m_shaderProgId;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADERPROGRAM_OPENGL4_HPP__
