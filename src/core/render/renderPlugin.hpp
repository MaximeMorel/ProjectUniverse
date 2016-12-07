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

    virtual const char* getSearchPath() const;

    virtual ShaderPtr createShader(const std::string& name, const std::string& fileName, Shader::Type t);
    virtual ShaderProgramPtr createShaderProgram(const std::string& name, const std::string& fileName);

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

private:

};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERPLUGIN_HPP__
