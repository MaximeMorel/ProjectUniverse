#ifndef __SHADERPROGRAM_OPENGL4_HPP__
#define __SHADERPROGRAM_OPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/shaderProgram.hpp"
#include "shader.hpp"
#include "opengltools.hpp"
#include <string>
#include <initializer_list>
////////////////////////////////////////////////////////////////////////////////
class ShaderProgramGL4 : public ShaderProgram
{
public:
    static ShaderProgramPtr create(const std::string& name,
                                   std::initializer_list<ShaderPtr> shaders = std::initializer_list<ShaderPtr>());


    virtual ~ShaderProgramGL4() override;

    virtual void bind() override;
    virtual void unbind() override;

    virtual void addShader(ShaderPtr shader) override;

    virtual bool link() override;

private:
    ShaderProgramGL4(const std::string& name,
                     std::initializer_list<ShaderPtr> shaders = std::initializer_list<ShaderPtr>());

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADERPROGRAM_OPENGL4_HPP__
