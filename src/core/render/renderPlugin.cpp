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
bool RenderPlugin::init()
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
const char* RenderPlugin::getShaderSearchPath() const
{
    return "";
}
////////////////////////////////////////////////////////////////////////////////
GfxContextType RenderPlugin::getRequiredContextType() const
{
    return GfxContextType::NONE;
}
////////////////////////////////////////////////////////////////////////////////
void RenderPlugin::resize(uint32_t x, uint32_t y)
{
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
void RenderPlugin::clear()
{

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
const RenderStats& RenderPlugin::getStats() const
{
    return m_renderStats;
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
Logger ENGINE_EXPORT & operator<<(Logger& o, const RenderPlugin& plugin)
{
    plugin.printOn(o);
    return o;
}
////////////////////////////////////////////////////////////////////////////////
RenderStats::RenderStats()
    : statNumMesh(0)
    , statNumTriangles(0)
{
}
////////////////////////////////////////////////////////////////////////////////
Logger ENGINE_EXPORT & operator<<(Logger& o, const RenderStats& stats)
{
    o << "meshes: " << stats.statNumMesh << " triangles: " << stats.statNumTriangles << "\n";
    return o;
}
////////////////////////////////////////////////////////////////////////////////
