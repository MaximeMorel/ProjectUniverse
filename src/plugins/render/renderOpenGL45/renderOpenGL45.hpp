#ifndef __RENDEROPENGL45_HPP__
#define __RENDEROPENGL45_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "renderOpenGL.hpp"
#include "renderopengl45_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL45_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL45_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL45_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginRenderOpenGL45 : public PluginRenderOpenGL
{
public:
    PluginRenderOpenGL45(Engine& engine);
    virtual ~PluginRenderOpenGL45() override;

    virtual bool init() override;

    virtual const char* getShaderSearchPath() const override;
    virtual GfxContextType getRequiredContextType() const override;

    virtual ShaderPtr createShader(const std::string& name, const std::string& fileName, Shader::Type t) override;
    virtual ShaderProgramPtr createShaderProgram(const std::string& name, const std::string& fileName) override;
    virtual TexturePtr createTexture(const std::string& name, const std::string& fileName) override;
    virtual BufferObjectPtr createBufferObject(const std::string& name) override;
    virtual RenderMeshPtr createRenderMesh(const std::string& name) override;

    virtual void draw() override;
    virtual void drawScene(Scene* scene) override;

    void getInfo();
};
/////////////////////////////////////////// /////////////////////////////////////
#endif // __RENDEROPENGL45_HPP__
