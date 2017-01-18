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
    return false;
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
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL::checkVersion(int major, int minor)
{
    GLint vmajor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &vmajor);
    GLint vminor = 0;
    glGetIntegerv(GL_MINOR_VERSION, &vminor);

    return (vmajor >= major && vminor >= minor);
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
