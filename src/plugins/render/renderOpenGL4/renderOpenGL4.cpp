////////////////////////////////////////////////////////////////////////////////
#include "renderOpenGL4.hpp"
#include "shader.hpp"
#include "shaderProgram.hpp"
#include "texture.hpp"
#include "vao.hpp"
#include "renderMesh.hpp"
#include "bufferObject.hpp"
#include "opengltools.hpp"
#include "core/log/logManager.hpp"
#include "core/resource/resourceManager.hpp"
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

    getInfo();
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderOpenGL4::~PluginRenderOpenGL4()
{
    log().log() << "PluginRenderOpenGL4 stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
const char* PluginRenderOpenGL4::getSearchPath() const
{
    return "shaders/opengl4/";
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL4::resize(uint32_t x, uint32_t y)
{
    glViewport(0, 0, x, y);
}
////////////////////////////////////////////////////////////////////////////////
VAOPtr PluginRenderOpenGL4::createVao(const std::string& name)
{
    return VAOGL4::create(name);
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr PluginRenderOpenGL4::createShader(const std::string& name, const std::string& fileName, Shader::Type t)
{
    return ShaderGL4::create(name, fileName, t);
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr PluginRenderOpenGL4::createShaderProgram(const std::string& name, const std::string& fileName)
{
    return ShaderProgramGL4::create(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr PluginRenderOpenGL4::createTexture(const std::string& name, const std::string& fileName)
{
    return TextureGL4::create(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectPtr PluginRenderOpenGL4::createBufferObject(const std::string& name)
{
    return BufferObjectGL4::create(name);
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshPtr PluginRenderOpenGL4::createRenderMesh(const std::string& name)
{
    return RenderMeshGL4::create(name);
}
////////////////////////////////////////////////////////////////////////////////
void PluginRenderOpenGL4::draw()
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
void PluginRenderOpenGL4::drawScene(Scene* scene)
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
void PluginRenderOpenGL4::getInfo()
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
}
////////////////////////////////////////////////////////////////////////////////
