#ifndef __SHADERPROGRAM_HPP__
#define __SHADERPROGRAM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include "shader.hpp"
#include <string>
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class ShaderProgram : public Resource
{
public:
    ShaderProgram(const std::string& name);

    virtual ~ShaderProgram() override;

    uint32_t getProgId() const;

    virtual void bind() const;
    virtual void unbind() const;

    virtual void addShader(ShaderPtr shader);

    virtual void link();

protected:
    uint32_t m_shaderProgId;

    std::vector<ShaderPtr> m_shaders;
};
////////////////////////////////////////////////////////////////////////////////
using ShaderProgramPtr = std::shared_ptr<ShaderProgram>;
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADERPROGRAM_HPP__
