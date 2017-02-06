#ifndef __RENDERPLUGIN_HPP__
#define __RENDERPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/log/logger.hpp"
#include "shader.hpp"
#include "shaderProgram.hpp"
#include "texture.hpp"
#include "vao.hpp"
#include "renderMesh.hpp"
#include "bufferObject.hpp"
#include "fbo.hpp"
#include "core/scene/scene.hpp"
#include "core/windowContext/windowContextTypes.hpp"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
struct ENGINE_EXPORT RenderStats
{
    RenderStats();
    friend Logger ENGINE_EXPORT & operator<<(Logger& o, const RenderStats& plugin);

    uint32_t statNumMesh;     ///< stats: number of mesh rendered during the last frame
    uint32_t statNumTriangles; ///< stats: number of triangles rendered during the last frame
};
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT RenderPlugin : public Library
{
public:
    RenderPlugin(Engine& engine);
    virtual ~RenderPlugin() override;

    virtual bool init();

    virtual const char* getShaderSearchPath() const;
    virtual GfxContextType getRequiredContextType() const;

    virtual void resize(uint32_t x, uint32_t y);

    virtual ShaderPtr createShader(const std::string& name, const std::string& fileName, Shader::Type t);
    virtual ShaderProgramPtr createShaderProgram(const std::string& name, const std::string& fileName);
    virtual TexturePtr createTexture(const std::string& name);
    virtual TexturePtr createTexture(const std::string& name, const std::string& fileName);
    virtual BufferObjectPtr createBufferObject(const std::string& name);
    virtual RenderMeshPtr createRenderMesh(const std::string& name);
    virtual FBOPtr createFBO(const std::string& name);


    virtual void clear();
    virtual void draw();
    virtual void drawScene(Scene* scene);

    const RenderStats& getStats() const;

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

protected:
    RenderStats m_renderStats;      ///< rendering stats container

private:
    friend Logger ENGINE_EXPORT & operator<<(Logger& o, const RenderPlugin& plugin);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERPLUGIN_HPP__
