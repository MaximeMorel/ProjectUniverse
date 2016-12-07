#ifndef __SHADERPROGRAM_NULL_HPP__
#define __SHADERPROGRAM_NULL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/shaderProgram.hpp"
#include "shader.hpp"
#include <string>
////////////////////////////////////////////////////////////////////////////////
class ShaderProgramNull : public ShaderProgram
{
public:
    ShaderProgramNull(const std::string& name, const std::string& fileName);

    virtual ~ShaderProgramNull() override;

    //virtual void addShader(Shader* shader) override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADERPROGRAM_NULL_HPP__
