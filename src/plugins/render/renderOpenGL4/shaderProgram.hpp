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
    static ShaderProgramPtr create(const std::string& name);
    ShaderProgramGL4(const std::string& name);

    virtual ~ShaderProgramGL4() override;

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void addShader(ShaderPtr shader) override;

    virtual void link() override;

protected:
    virtual void printOn(Logger& o) const;

private:
    uint32_t m_shaderProgId;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADERPROGRAM_OPENGL4_HPP__
