////////////////////////////////////////////////////////////////////////////////
#include "renderPlugin.hpp"
////////////////////////////////////////////////////////////////////////////////
RenderPlugin::RenderPlugin(Engine &engine)
    : Library(engine)
{
}
////////////////////////////////////////////////////////////////////////////////
RenderPlugin::~RenderPlugin()
{
}
////////////////////////////////////////////////////////////////////////////////
const char* RenderPlugin::getSearchPath() const
{
    return "";
}
////////////////////////////////////////////////////////////////////////////////
void RenderPlugin::resize(uint32_t x, uint32_t y)
{
}
////////////////////////////////////////////////////////////////////////////////
VAOPtr RenderPlugin::createVao(const std::string& name)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr RenderPlugin::createShader(const std::string& name, const std::string& fileName, Shader::Type t)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr RenderPlugin::createShaderProgram(const std::string& name, const std::string& fileName)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr RenderPlugin::createTexture(const std::string& name, const std::string& fileName)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectPtr RenderPlugin::createBufferObject(const std::string& name)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshPtr RenderPlugin::createRenderMesh(const std::string& name)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
void RenderPlugin::draw()
{
}
////////////////////////////////////////////////////////////////////////////////
void RenderPlugin::drawScene(Scene* scene)
{
}
////////////////////////////////////////////////////////////////////////////////
size_t RenderPlugin::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
void RenderPlugin::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const RenderPlugin& plugin)
{
    plugin.printOn(o);
    return o;
}
////////////////////////////////////////////////////////////////////////////////
