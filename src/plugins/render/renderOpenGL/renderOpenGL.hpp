#ifndef __RENDEROPENGL_HPP__
#define __RENDEROPENGL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/render/renderPlugin.hpp"
////////////////////////////////////////////////////////////////////////////////
class PluginRenderOpenGL : public RenderPlugin
{
public:
    PluginRenderOpenGL(Engine& engine);
    virtual ~PluginRenderOpenGL() override;

    virtual bool init() override;

    virtual const char* getShaderSearchPath() const override;

    void resize(uint32_t x, uint32_t y) override;

    virtual ShaderPtr createShader(const std::string& name, const std::string& fileName, Shader::Type t) override;
    virtual ShaderProgramPtr createShaderProgram(const std::string& name, const std::string& fileName) override;
    virtual TexturePtr createTexture(const std::string& name, const std::string& fileName) override;
    virtual BufferObjectPtr createBufferObject(const std::string& name) override;
    virtual RenderMeshPtr createRenderMesh(const std::string& name) override;

    virtual void draw() override;
    virtual void drawScene(Scene* scene) override;

protected:
    bool initGlew(bool experimental);
    virtual bool checkExtensions();

    virtual void logInfoVersion(Logger& o) const;
    virtual void logInfoExtensions(Logger& o) const;
    virtual void logInfoMisc(Logger& o) const;

    virtual bool checkVersion(int major, int minor);

protected:

    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDEROPENGL_HPP__
