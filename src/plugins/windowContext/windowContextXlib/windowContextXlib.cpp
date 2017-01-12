////////////////////////////////////////////////////////////////////////////////
#include "windowContextXlib.hpp"
#include "core/log/logManager.hpp"
#include "X11/Xlib.h"
#include "GL/glx.h"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "windowXlib",
                          "WindowXlib",
                          "window",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginWindowContextXlib* lib = nullptr;
////////////////////////////////////////////////////////////////////////////////
const PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Library* getLibInstance(Engine* engine)
{
    if (lib == nullptr)
    {
        lib = new PluginWindowContextXlib(*engine);
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
PluginWindowContextXlib::PluginWindowContextXlib(Engine &engine)
    : WindowPlugin(engine)
{
    log().log() << "PluginWindowContextXlib start...\n";

    XEvent e;

    Display *d = XOpenDisplay(NULL);
    int s = DefaultScreen(d);
    Window w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
}
////////////////////////////////////////////////////////////////////////////////
PluginWindowContextXlib::~PluginWindowContextXlib()
{
    log().log() << "PluginWindowContextXlib stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
void PluginWindowContextXlib::update()
{
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextXlib::setResolution(uint32_t x, uint32_t y)
{
    WindowPlugin::setResolution(x, y);

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextXlib::setPosition(Vec2i position)
{
    WindowPlugin::setPosition(position);

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextXlib::setTitle(const std::string& title)
{
    WindowPlugin::setTitle(title);

    return false;
}
////////////////////////////////////////////////////////////////////////////////
void PluginWindowContextXlib::swapBuffers()
{
    GLXDrawable drawable = 0;
    glXSwapBuffers(0, drawable);
}
////////////////////////////////////////////////////////////////////////////////
