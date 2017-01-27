////////////////////////////////////////////////////////////////////////////////
#include "renderOpenGL45.hpp"
#include "shaderGL45.hpp"
#include "shaderProgramGL45.hpp"
#include "textureGL45.hpp"
#include "vaoGL45.hpp"
#include "renderMeshGL45.hpp"
#include "bufferObjectGL45.hpp"
#include "opengltools.hpp"
#include "core/log/logManager.hpp"
#include "core/resource/resourceManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "renderOpenGL45",
                          "renderOpenGL45",
                          "render",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL45* lib = nullptr;
/////////////////////////input///////////////////////////////////////////////////////
const PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Library* getLibInstance(Engine* engine)
{
    if (lib == nullptr)
    {
        lib = new PluginRenderOpenGL45(*engine);
    }
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void closeLibInstance()
{
    delete lib;
    lib = nullptr;
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL45::PluginRenderOpenGL45(Engine &engine)
    : PluginRenderOpenGL(engine)
{
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL45::~PluginRenderOpenGL45()
{
    log().log() << "PluginRenderOpenGL45 stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL45::init()
{
    log().log() << "PluginRenderOpenGL45 start...\n";

    bool res = PluginRenderOpenGL::init();
    if (res == false)
        return false;

    if (checkVersion(3, 3) == false)
        return false;

    log().log() << *this << "\n";

    return true;
}
////////////////////////////////////////////////////////////////////////////////
const char* PluginRenderOpenGL45::getShaderSearchPath() const
{
    return "shaders/opengl45/";
}
////////////////////////////////////////////////////////////////////////////////
GfxContextType PluginRenderOpenGL45::getRequiredContextType() const
{
    return GfxContextType::OPENGL_4_5;
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr PluginRenderOpenGL45::createShader(const std::string& name, const std::string& fileName, Shader::Type t)
{
    return ShaderGL45::create(name, fileName, t);
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr PluginRenderOpenGL45::createShaderProgram(const std::string& name, const std::string& fileName)
{
    return ShaderProgramGL45::create(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr PluginRenderOpenGL45::createTexture(const std::string& name, const std::string& fileName)
{
    return TextureGL45::create(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectPtr PluginRenderOpenGL45::createBufferObject(const std::string& name)
{
    return BufferObjectGL45::create(name);
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshPtr PluginRenderOpenGL45::createRenderMesh(const std::string& name)
{
    return RenderMeshGL45::create(name);
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL45::draw()
{
    PluginRenderOpenGL::draw();
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL45::drawScene(Scene* scene)
{
    PluginRenderOpenGL::drawScene(scene);
}
////////////////////////////////////////////////////////////////////////////////
