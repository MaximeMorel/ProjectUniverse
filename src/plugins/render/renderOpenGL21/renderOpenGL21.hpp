#ifndef __RENDEROPENGL21_HPP__
#define __RENDEROPENGL21_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "renderOpenGL.hpp"
#include "renderopengl21_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL21_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL21_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL21_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginRenderOpenGL21 : public PluginRenderOpenGL
{
public:
    PluginRenderOpenGL21(Engine& engine);
    virtual ~PluginRenderOpenGL21() override;

    virtual bool init() override;

    virtual const char* getShaderSearchPath() const override;

    virtual ShaderPtr createShader(const std::string& name, const std::string& fileName, Shader::Type t) override;
    virtual ShaderProgramPtr createShaderProgram(const std::string& name, const std::string& fileName) override;
    virtual TexturePtr createTexture(const std::string& name, const std::string& fileName) override;
    virtual BufferObjectPtr createBufferObject(const std::string& name) override;
    virtual RenderMeshPtr createRenderMesh(const std::string& name) override;

    virtual void draw() override;
    virtual void drawScene(Scene* scene) override;

    virtual void logInfoExtensions(Logger& o) const override;
};
/////////////////////////////////////////// /////////////////////////////////////
#endif // __RENDEROPENGL21_HPP__
