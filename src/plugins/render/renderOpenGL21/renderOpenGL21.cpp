////////////////////////////////////////////////////////////////////////////////
#include "renderOpenGL21.hpp"
#include "shaderGL21.hpp"
#include "shaderProgramGL21.hpp"
#include "textureGL21.hpp"
#include "renderMeshGL21.hpp"
#include "bufferObjectGL21.hpp"
#include "opengltools.hpp"
#include "core/log/logManager.hpp"
#include "core/resource/resourceManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "renderOpenGL21",
                          "renderOpenGL21",
                          "render",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL21* lib = nullptr;
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
        lib = new PluginRenderOpenGL21(*engine);
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
PluginRenderOpenGL21::PluginRenderOpenGL21(Engine &engine)
    : PluginRenderOpenGL(engine)
{
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL21::~PluginRenderOpenGL21()
{
    log().log() << "PluginRenderOpenGL21 stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL21::init()
{
    log().log() << "PluginRenderOpenGL21 start...\n";

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        log().log() << "GLEW Error: " << glewGetErrorString(err) << "\n";
        return false;
    }

    log().log() << "GLEW_VERSION: " << reinterpret_cast<const char*>(glewGetString(GLEW_VERSION)) << "\n";

    if (checkVersion(2, 1) == false)
        return false;

    log().log() << *this << "\n";

    return true;
}
////////////////////////////////////////////////////////////////////////////////
const char* PluginRenderOpenGL21::getShaderSearchPath() const
{
    return "shaders/opengl21/";
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr PluginRenderOpenGL21::createShader(const std::string& name, const std::string& fileName, Shader::Type t)
{
    return ShaderGL21::create(name, fileName, t);
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr PluginRenderOpenGL21::createShaderProgram(const std::string& name, const std::string& fileName)
{
    return ShaderProgramGL21::create(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr PluginRenderOpenGL21::createTexture(const std::string& name, const std::string& fileName)
{
    return TextureGL21::create(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectPtr PluginRenderOpenGL21::createBufferObject(const std::string& name)
{
    return BufferObjectGL21::create(name);
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshPtr PluginRenderOpenGL21::createRenderMesh(const std::string& name)
{
    return RenderMeshGL21::create(name);
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL21::draw()
{
    PluginRenderOpenGL::draw();
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL21::drawScene(Scene* scene)
{
    PluginRenderOpenGL::drawScene(scene);
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL21::logInfoExtensions(Logger& o) const
{
    const GLubyte* str = glGetString(GL_EXTENSIONS);
    o << "GL_EXTENSIONS: " << reinterpret_cast<const char*>(str) << "\n";
    /*uint32_t i = 0;
    std::string strExt;
    while (str)
    {
        const GLubyte* strStart = str;
        while (*str != ' ' || *str)
            ++str;
        strExt = std::string(strStart, str);
        o << "GL_EXTENSION " << i << ": " << strExt << "\n";
    }*/
}
////////////////////////////////////////////////////////////////////////////////
