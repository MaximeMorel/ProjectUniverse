////////////////////////////////////////////////////////////////////////////////
#include "core/log/logManager.hpp"
#include "renderManager.hpp"
#include "renderPlugin.hpp"
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
RenderManager* gRender = nullptr;
////////////////////////////////////////////////////////////////////////////////
RenderManager::RenderManager()
    : m_plugin(nullptr)
{
}
////////////////////////////////////////////////////////////////////////////////
RenderManager::~RenderManager()
{
}
////////////////////////////////////////////////////////////////////////////////
bool RenderManager::setPlugin(PluginLibPtr renderPlugin)
{
    if (m_plugin)
    {
        // clean current plugin
        log().log() << "Removing current Render Plugin\n";
    }
    const PluginInfo& pluginInfo = renderPlugin->getInfo();
    if (pluginInfo.type == std::string("render"))
    {
        RenderPlugin* plugin = static_cast<RenderPlugin*>(renderPlugin->getLibInstance(&getEngine()));
        if (plugin->init() == true)
        {
            m_plugin = plugin;
            log().log() << "Render Plugin set\n";
            return true;
        }
    }
    else
    {
        log().log() << "Wrong Render Plugin\n";
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
size_t RenderManager::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
void RenderManager::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
void setGlobalRender(RenderManager& render)
{
    gRender = &render;
}
////////////////////////////////////////////////////////////////////////////////
RenderManager& render()
{
    return *gRender;
}
////////////////////////////////////////////////////////////////////////////////
