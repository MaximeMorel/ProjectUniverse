#ifndef __WINDOWMANAGER_HPP__
#define __WINDOWMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/plugin.hpp"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
class WindowPlugin;
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT WindowManager
{
public:
    WindowManager();
    ~WindowManager();

    bool setPlugin(PluginLibPtr windowPlugin);

    WindowPlugin* getWindow();

    /// create graphic context according to the render plugin name
    bool createContext(const std::string& render);

private:
    WindowPlugin* m_plugin;
};
////////////////////////////////////////////////////////////////////////////////
/// Global window access
void setGlobalWindow(WindowManager& window);
WindowManager ENGINE_EXPORT & window();
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWMANAGER_HPP__

