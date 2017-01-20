////////////////////////////////////////////////////////////////////////////////
#include "renderOpenGL.hpp"
#include "shaderGL.hpp"
#include "shaderProgramGL.hpp"
#include "textureGL.hpp"
#include "vaoGL.hpp"
#include "renderMeshGL.hpp"
#include "bufferObjectGL.hpp"
#include "opengltools.hpp"
#include "core/log/logManager.hpp"
#include "core/resource/resourceManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL::PluginRenderOpenGL(Engine &engine)
    : RenderPlugin(engine)
{
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL::~PluginRenderOpenGL()
{
    log().log() << "PluginRenderOpenGL stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL::init()
{
    if (initGlew(false) == false)
        return false;

    if (checkExtensions() == false)
    {
        log().log() << "Could not load OpenGL extensions.\n";
        if (initGlew(true) == false)
            return false;

        if (checkExtensions() == false)
        {
            log().log() << "Could not load OpenGL extensions with GLEW expermiental.\n";
            return false;
        }
        else
        {
            log().log() << "OpenGL extensions loaded with GLEW expermiental.\n";
        }
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
const char* PluginRenderOpenGL::getShaderSearchPath() const
{
    return "shaders/opengl/";
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL::resize(uint32_t x, uint32_t y)
{
    glViewport(0, 0, x, y);
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr PluginRenderOpenGL::createShader(const std::string& name, const std::string& fileName, Shader::Type t)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr PluginRenderOpenGL::createShaderProgram(const std::string& name, const std::string& fileName)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr PluginRenderOpenGL::createTexture(const std::string& name, const std::string& fileName)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectPtr PluginRenderOpenGL::createBufferObject(const std::string& name)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshPtr PluginRenderOpenGL::createRenderMesh(const std::string& name)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL::draw()
{
    //glFlushErrors();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, 1);
    glFlush();
    //glLogCurrentError();
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL::drawScene(Scene* scene)
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (Mesh* mesh : scene->m_meshes)
    {
        if (!mesh->m_renderMesh)
        {
            mesh->m_renderMesh = res().create<RenderMesh>(mesh->getName());
            if (mesh->m_renderMesh)
            {
                mesh->m_renderMesh->setup(mesh);
            }
        }
        if (mesh->m_renderMesh)
        {
            mesh->m_renderMesh->draw();
        }
    }
    glLogCurrentError();
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL::initGlew(bool experimental)
{
    glewExperimental = experimental;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        log().log() << "GLEW Error: " << glewGetErrorString(err) << "\n";
        return false;
    }

    log().log() << "GLEW_VERSION: " << reinterpret_cast<const char*>(glewGetString(GLEW_VERSION)) << "\n";

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL::checkExtensions()
{
    return true;
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL::logInfoVersion(Logger& o) const
{
    const GLubyte* str = nullptr;

    str = glGetString(GL_VENDOR);
    o << "GL_VENDOR: " << reinterpret_cast<const char*>(str) << "\n";

    str = glGetString(GL_RENDERER);
    o << "GL_RENDERER: " << reinterpret_cast<const char*>(str) << "\n";

    str = glGetString(GL_VERSION);
    o << "GL_VERSION: " << reinterpret_cast<const char*>(str);

    GLint v = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &v);
    o <<  " (" << v;
    glGetIntegerv(GL_MINOR_VERSION, &v);
    o <<  "." << v << ")\n";

    str = glGetString(GL_SHADING_LANGUAGE_VERSION);
    o << "GL_SHADING_LANGUAGE_VERSION: " << reinterpret_cast<const char*>(str) << "\n";
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL::logInfoExtensions(Logger& o) const
{
    GLint v = 0;
    const GLubyte* str = nullptr;

    glGetIntegerv(GL_NUM_EXTENSIONS, &v);
    for (GLint i = 0; i < v; ++i)
    {
        str = glGetStringi(GL_EXTENSIONS, i);
        o << "GL_EXTENSION " << i << ": " << reinterpret_cast<const char*>(str) << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL::logInfoMisc(Logger& o) const
{
    GLint v = 0;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &v);
    o << "GL_MAX_TEXTURE_SIZE: " << v << "\n";

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v);
    o << "GL_MAX_VERTEX_ATTRIBS: " << v << "\n";

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &v);
    o << "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: " << v << "\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL::checkVersion(int major, int minor)
{
    GLint vmajor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &vmajor);
    GLint vminor = 0;
    glGetIntegerv(GL_MINOR_VERSION, &vminor);

    if (vmajor > major)
        return true;
    if (vmajor == major && vminor >= minor)
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL::printOn(Logger& o) const
{
    o << "PluginRenderOpenGL:\n";
    logInfoVersion(o);
    logInfoExtensions(o);
    logInfoMisc(o);
}
////////////////////////////////////////////////////////////////////////////////
