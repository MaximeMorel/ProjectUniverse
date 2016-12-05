#ifndef __RENDEROPENGL4_HPP__
#define __RENDEROPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/render/renderPlugin.hpp"
#include "shader.hpp"
#include "shaderProgram.hpp"
#include "renderopengl4_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL4_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL4_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL4_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginRenderOpenGL4 : public RenderPlugin
{
public:
    PluginRenderOpenGL4(Engine& engine);
    virtual ~PluginRenderOpenGL4() override;

    virtual ShaderPtr createShader(const std::string& name, Shader::Type t) override;
    virtual ShaderProgramPtr createShaderProgram(const std::string& name, std::initializer_list<ShaderPtr> shaders) override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDEROPENGL4_HPP__
