#ifndef __RENDERMANAGER_HPP__
#define __RENDERMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/plugin.hpp"
#include "core/log/logger.hpp"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
class RenderPlugin;
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT RenderManager
{
public:
    RenderManager();
    ~RenderManager();

    bool setPlugin(PluginLibPtr renderPlugin);

    RenderPlugin* impl()
    {
        return m_plugin;
    }

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

private:
    RenderPlugin* m_plugin;
};
////////////////////////////////////////////////////////////////////////////////
/// Global render access
void setGlobalRender(RenderManager& render);
RenderManager ENGINE_EXPORT & render();
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERMANAGER_HPP__
