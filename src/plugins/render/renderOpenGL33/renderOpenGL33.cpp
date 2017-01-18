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
    : RenderPlugin(engine)
{
    log().log() << "PluginRenderOpenGL33 start...\n";

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        log().log() << "GLEW Error: " << glewGetErrorString(err) << "\n";
    }
    else
    {
        log().log() << "GLEW_VERSION: " << reinterpret_cast<const char*>(glewGetString(GLEW_VERSION)) << "\n";
        //log().log() << "GLEW_ARB_vertex_type_2_10_10_10_rev: " << GLEW_ARB_vertex_type_2_10_10_10_rev << "\n";
        log().log() << "GLEW_ARB_vertex_array_object: " << GLEW_ARB_vertex_array_object << "\n";
    }

    getInfo();
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL33::~PluginRenderOpenGL33()
{
    log().log() << "PluginRenderOpenGL33 stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginRenderOpenGL33::init()
{
    return false;
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
    //glFlushErrors();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, 1);
    glFlush();
    //glLogCurrentError();
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL33::drawScene(Scene* scene)
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
void PluginRenderOpenGL33::getInfo()
{
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

    glGetIntegerv(GL_NUM_EXTENSIONS, &v);
    for (GLint i = 0; i < v; ++i)
    {
        str = glGetStringi(GL_EXTENSIONS, i);
        log().log() << "GL_EXTENSION " << i << ": " << reinterpret_cast<const char*>(str) << "\n";
    }

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &v);
    log().log() << "GL_MAX_TEXTURE_SIZE: " << v << "\n";

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v);
    log().log() << "GL_MAX_VERTEX_ATTRIBS: " << v << "\n";
}
////////////////////////////////////////////////////////////////////////////////
