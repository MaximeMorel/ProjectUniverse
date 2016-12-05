////////////////////////////////////////////////////////////////////////////////
#include "renderOpenGL4.hpp"
//#include <GL/gl.h>
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "renderOpenGL4",
                          "renderOpenGL4",
                          "render",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL4* lib = nullptr;
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
        lib = new PluginRenderOpenGL4(*engine);
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
PluginRenderOpenGL4::PluginRenderOpenGL4(Engine &engine)
    : RenderPlugin(engine)
{
    log().log() << "PluginRenderOpenGL4 start...\n";

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        log().log() << "GLEW Error: " << glewGetErrorString(err) << "\n";
    }
    else
    {
        log().log() << "GLEW_VERSION: " << reinterpret_cast<const char*>(glewGetString(GLEW_VERSION)) << "\n";
    }

    const GLubyte* str = nullptr;

    str = glGetString(GL_VENDOR);
    log().log() << "GL_VENDOR: " << reinterpret_cast<const char*>(str) << "\n";

    str = glGetString(GL_RENDERER);
    log().log() << "GL_RENDERER: " << reinterpret_cast<const char*>(str) << "\n";

    str = glGetString(GL_VERSION);
    log().log() << "GL_VERSION: " << reinterpret_cast<const char*>(str);

    GLint v = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &v);
    log().log() <<  " (" << v;
    glGetIntegerv(GL_MINOR_VERSION, &v);
    log().log() <<  "." << v << ")\n";

    str = glGetString(GL_SHADING_LANGUAGE_VERSION);
    log().log() << "GL_SHADING_LANGUAGE_VERSION: " << reinterpret_cast<const char*>(str) << "\n";

    str = glGetString(GL_EXTENSIONS);
    log().log() << "GL_EXTENSIONS: " << reinterpret_cast<const char*>(str) << "\n";
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL4::~PluginRenderOpenGL4()
{
    log().log() << "PluginRenderOpenGL4 stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr PluginRenderOpenGL4::createShader(const std::string& name, Shader::Type t)
{
    return ShaderGL4::create(name, t);
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr PluginRenderOpenGL4::createShaderProgram(const std::string& name, std::initializer_list<ShaderPtr> shaders)
{
    return ShaderProgramGL4::create(name, shaders);
}
////////////////////////////////////////////////////////////////////////////////
