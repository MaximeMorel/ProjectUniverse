#ifndef __WINDOWCONTEXTXLIB_HPP__
#define __WINDOWCONTEXTXLIB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/windowContext/windowPlugin.hpp"
#include "windowcontextxlib_export.h"
#include "X11/Xlib.h"
#include "GL/glx.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" WINDOWCONTEXTXLIB_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" WINDOWCONTEXTXLIB_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" WINDOWCONTEXTXLIB_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginWindowContextXlib : public WindowPlugin
{
public:
    PluginWindowContextXlib(Engine &engine);
    virtual ~PluginWindowContextXlib() override;

    virtual void update() override;

    virtual bool setResolution(uint32_t x, uint32_t y) override;

    virtual bool setPosition(uint32_t x, uint32_t y) override;

    virtual bool setTitle(const std::string& title) override;

    virtual void swapBuffers() override;

private:
    Display* m_display;
    Window m_window;
    Colormap m_colorMap;
    GLXContext m_glxCtx;
    Atom m_wmDeleteMessage;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWCONTEXTXLIB_HPP__
