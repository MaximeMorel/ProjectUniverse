#ifndef __RENDERPLUGIN_HPP__
#define __RENDERPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/log/logger.hpp"
#include "shader.hpp"
#include "shaderProgram.hpp"
#include "texture.hpp"
#include "vao.hpp"
#include "gpuMesh.hpp"
#include "bufferObject.hpp"
#include "core/scene/scene.hpp"
////////////////////////////////////////////////////////////////////////////////
class RenderPlugin : public Library
{
public:
    RenderPlugin(Engine& engine);
    virtual ~RenderPlugin() override;

    virtual const char* getSearchPath() const;

    virtual void resize(uint32_t x, uint32_t y);

    virtual VAOPtr createVao(const std::string& name);
    virtual ShaderPtr createShader(const std::string& name, const std::string& fileName, Shader::Type t);
    virtual ShaderProgramPtr createShaderProgram(const std::string& name, const std::string& fileName);
    virtual TexturePtr createTexture(const std::string& name, const std::string& fileName);
    virtual BufferObjectPtr createBufferObject(const std::string& name);
    virtual GPUMeshPtr createGPUMesh(const std::string& name);

    virtual void draw();
    virtual void drawScene(Scene* scene);

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

private:

};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERPLUGIN_HPP__
