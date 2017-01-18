////////////////////////////////////////////////////////////////////////////////
#include "renderOpenGL33.hpp"
#include "shaderGL33.hpp"
#include "shaderProgramGL33.hpp"
#include "textureGL33.hpp"
#include "vaoGL33.hpp"
#include "renderMeshGL33.hpp"
#include "bufferObjectGL33.hpp"
#include "opengltools.hpp"
#include "core/log/logManager.hpp"
#include "core/resource/resourceManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "renderOpenGL33",
                          "renderOpenGL33",
                          "render",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL33* lib = nullptr;
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
        lib = new PluginRenderOpenGL33(*engine);
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
PluginRenderOpenGL33::PluginRenderOpenGL33(Engine &engine)
    : PluginRenderOpenGL(engine)
{
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL33::~PluginRenderOpenGL33()
{
    log().log() << "PluginRenderOpenGL33 stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL33::init()
{
    log().log() << "PluginRenderOpenGL33 start...\n";

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        log().log() << "GLEW Error: " << glewGetErrorString(err) << "\n";
        return false;
    }

    log().log() << "GLEW_VERSION: " << reinterpret_cast<const char*>(glewGetString(GLEW_VERSION)) << "\n";

    if (checkVersion(3, 3) == false)
        return false;

    log().log() << *this << "\n";

    return true;
}
////////////////////////////////////////////////////////////////////////////////
const char* PluginRenderOpenGL33::getShaderSearchPath() const
{
    return "shaders/opengl33/";
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr PluginRenderOpenGL33::createShader(const std::string& name, const std::string& fileName, Shader::Type t)
{
    return ShaderGL33::create(name, fileName, t);
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr PluginRenderOpenGL33::createShaderProgram(const std::string& name, const std::string& fileName)
{
    return ShaderProgramGL33::create(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr PluginRenderOpenGL33::createTexture(const std::string& name, const std::string& fileName)
{
    return TextureGL33::create(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectPtr PluginRenderOpenGL33::createBufferObject(const std::string& name)
{
    return BufferObjectGL33::create(name);
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshPtr PluginRenderOpenGL33::createRenderMesh(const std::string& name)
{
    return RenderMeshGL33::create(name);
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL33::draw()
{
    PluginRenderOpenGL::draw();
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL33::drawScene(Scene* scene)
{
    PluginRenderOpenGL::drawScene(scene);
}
////////////////////////////////////////////////////////////////////////////////
