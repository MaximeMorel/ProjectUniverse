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
#include <cstring>
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

    bool res = PluginRenderOpenGL::init();
    if (res == false)
        return false;

    if (checkVersion(2, 1) == false)
        return false;

    log().log() << *this << "\n";

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL21::checkExtensions()
{
    return GLEW_ARB_framebuffer_object;
}
////////////////////////////////////////////////////////////////////////////////
const char* PluginRenderOpenGL21::getShaderSearchPath() const
{
    return "shaders/opengl21/";
}
////////////////////////////////////////////////////////////////////////////////
GfxContextType PluginRenderOpenGL21::getRequiredContextType() const
{
    return GfxContextType::OPENGL_2_1;
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
void PluginRenderOpenGL21::logInfoVersion(Logger& o) const
{
    const GLubyte* str = nullptr;

    str = glGetString(GL_VENDOR);
    o << "GL_VENDOR: " << reinterpret_cast<const char*>(str) << "\n";

    str = glGetString(GL_RENDERER);
    o << "GL_RENDERER: " << reinterpret_cast<const char*>(str) << "\n";

    str = glGetString(GL_VERSION);
    o << "GL_VERSION: " << reinterpret_cast<const char*>(str) << "\n";

    str = glGetString(GL_SHADING_LANGUAGE_VERSION);
    o << "GL_SHADING_LANGUAGE_VERSION: " << reinterpret_cast<const char*>(str) << "\n";
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL21::logInfoExtensions(Logger& o) const
{
    const GLubyte* str = glGetString(GL_EXTENSIONS);
    uint32_t i = 0;
    std::string strExt;
    while (str && *str)
    {
        const GLubyte* strStart = str;
        while (*str && *str != ' ')
            ++str;
        strExt = std::string(strStart, str);
        o << "GL_EXTENSION " << i << ": " << strExt << "\n";
        ++i;
        ++str;

        if (i > 1000)
            break;
    }
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL21::checkVersion(int major, int minor)
{
    const GLubyte* str = glGetString(GL_VERSION);
    if (str)
    {
        GLint vmajor = 0;
        GLint vminor = 0;
        if (strlen(reinterpret_cast<const char*>(str)) >= 3)
        {
            if (str[0] >= '0' && str[0] <= '9' && str[2] >= '0' && str[2] <= '9')
            {
                vmajor = str[0] - '0';
                vminor = str[2] - '0';
                if (vmajor > major)
                    return true;
                if (vmajor == major && vminor >= minor)
                    return true;
            }
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
