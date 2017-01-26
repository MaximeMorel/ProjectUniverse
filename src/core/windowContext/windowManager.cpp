////////////////////////////////////////////////////////////////////////////////
#include "windowManager.hpp"
#include "windowPlugin.hpp"
#include "core/log/logManager.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/config/config.hpp"
#include "core/engineFwd.hpp"
////////////////////////////////////////////////////////////////////////////////
WindowManager* gWindow = nullptr;
////////////////////////////////////////////////////////////////////////////////
WindowManager::WindowManager()
    : m_plugin(nullptr)
{
}
////////////////////////////////////////////////////////////////////////////////
WindowManager::~WindowManager()
{
}
////////////////////////////////////////////////////////////////////////////////
bool WindowManager::setPlugin(PluginLibPtr windowPlugin)
{
    if (m_plugin)
    {
        // clean current plugin
        log().log() << "Removing current WindowContext Plugin\n";
    }
    const PluginInfo& pluginInfo = windowPlugin->getInfo();
    if (pluginInfo.type == std::string("window"))
    {
        WindowPlugin* plugin = static_cast<WindowPlugin*>(windowPlugin->getLibInstance(&getEngine()));
        m_plugin = plugin;

        log().log() << "WindowContext Plugin set\n";
        return true;
    }
    else
    {
        log().log() << "Wrong WindowContext Plugin\n";
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
WindowPlugin* WindowManager::getWindow()
{
    return m_plugin;
}
////////////////////////////////////////////////////////////////////////////////
bool WindowManager::createContext(const std::string& render)
{
    if (m_plugin)
    {
        GfxContextType type = GfxContextType::NONE;
        if (render == "RenderOpenGL21")
            type = GfxContextType::OPENGL_2_1;
        else if (render == "RenderOpenGL33")
            type = GfxContextType::OPENGL_3_3;
        else if (render == "RenderOpenGL45")
            type = GfxContextType::OPENGL_4_5;
        return m_plugin->createContext(type);
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void setGlobalWindow(WindowManager& window)
{
    gWindow = &window;
}
////////////////////////////////////////////////////////////////////////////////
WindowManager& window()
{
    return *gWindow;
}
////////////////////////////////////////////////////////////////////////////////
