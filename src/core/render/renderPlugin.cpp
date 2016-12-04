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
ShaderPtr RenderPlugin::createShader(const std::string& name, Shader::Type t)
{

}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr RenderPlugin::createShaderProgram(const std::string& name)
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
