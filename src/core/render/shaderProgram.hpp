#ifndef __SHADERPROGRAM_HPP__
#define __SHADERPROGRAM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include "shader.hpp"
#include <string>
////////////////////////////////////////////////////////////////////////////////
class ShaderProgram : public Resource
{
public:
    ShaderProgram(const std::string& name);

    virtual ~ShaderProgram() override;

    //virtual void addShader(Shader* shader);

protected:
    unsigned int m_shaderProgId;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADERPROGRAM_HPP__
