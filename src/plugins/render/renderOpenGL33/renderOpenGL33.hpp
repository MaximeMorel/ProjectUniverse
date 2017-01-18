#ifndef __RENDEROPENGL33_HPP__
#define __RENDEROPENGL33_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "renderOpenGL.hpp"
#include "renderopengl33_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL33_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL33_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDEROPENGL33_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginRenderOpenGL33 : public PluginRenderOpenGL
{
public:
    PluginRenderOpenGL33(Engine& engine);
    virtual ~PluginRenderOpenGL33() override;

    virtual bool init() override;

    virtual const char* getShaderSearchPath() const override;

    virtual ShaderPtr createShader(const std::string& name, const std::string& fileName, Shader::Type t) override;
    virtual ShaderProgramPtr createShaderProgram(const std::string& name, const std::string& fileName) override;
    virtual TexturePtr createTexture(const std::string& name, const std::string& fileName) override;
    virtual BufferObjectPtr createBufferObject(const std::string& name) override;
    virtual RenderMeshPtr createRenderMesh(const std::string& name) override;

    virtual void draw() override;
    virtual void drawScene(Scene* scene) override;
};
/////////////////////////////////////////// /////////////////////////////////////
#endif // __RENDEROPENGL33_HPP__
