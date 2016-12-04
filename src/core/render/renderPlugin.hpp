#ifndef __RENDERPLUGIN_HPP__
#define __RENDERPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/log/logger.hpp"
#include "shader.hpp"
#include "shaderProgram.hpp"
////////////////////////////////////////////////////////////////////////////////
class RenderPlugin : public Library
{
public:
    RenderPlugin(Engine& engine);
    virtual ~RenderPlugin() override;

    virtual ShaderPtr createShader(const std::string& name, Shader::Type t);
    virtual ShaderProgramPtr createShaderProgram(const std::string& name);

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

private:

};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERPLUGIN_HPP__
