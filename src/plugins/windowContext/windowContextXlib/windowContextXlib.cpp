////////////////////////////////////////////////////////////////////////////////
#include "windowContextXlib.hpp"
#include "core/log/logManager.hpp"
#include "GL/glxext.h"
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
    , m_display(nullptr)
    , m_window(0)
    , m_glxCtx(nullptr)
{
    log().log() << "PluginWindowContextXlib start...\n";

    m_display = XOpenDisplay(nullptr);
    if (!m_display)
    {
      log().log() << "Failed to open X display\n";
      return;
    }

    int glxMajor = 0;
    int glxMinor = 0;
    if (!glXQueryVersion(m_display, &glxMajor, &glxMinor))
    {
        log().log() << "Failed to query GLX version\n";
    }
    log().log() << "GLX version: " << glxMajor << "." << glxMinor << "\n";

    int visualAttribs[] =
    {
        GLX_X_RENDERABLE    , True,
        GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
        GLX_RENDER_TYPE     , GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
        GLX_RED_SIZE        , 8,
        GLX_GREEN_SIZE      , 8,
        GLX_BLUE_SIZE       , 8,
        GLX_ALPHA_SIZE      , 8,
        GLX_DEPTH_SIZE      , 24,
        GLX_STENCIL_SIZE    , 8,
        GLX_DOUBLEBUFFER    , True,
        //GLX_SAMPLE_BUFFERS  , 1,
        //GLX_SAMPLES         , 4,
        None
    };

    int fbcount;
    GLXFBConfig* fbconfigs = glXChooseFBConfig(m_display, DefaultScreen(m_display), visualAttribs, &fbcount);
    if (!fbconfigs)
    {
        log().log() << "Failed to retrieve a framebuffer config\n";
        return;
    }
    log().log() << "Found " << fbcount << " matching FB configs.\n";

    GLXFBConfig fbconfig = fbconfigs[0];
    XFree(fbconfigs);

    XVisualInfo* vi = glXGetVisualFromFBConfig(m_display, fbconfig);
    if (!vi)
    {
        log().log() << "Cannot get visual from frame buffer configuration\n";
        return;
    }

    XSetWindowAttributes windowAttribs;
    m_colorMap = XCreateColormap(m_display, RootWindow(m_display, vi->screen), vi->visual, AllocNone);
    windowAttribs.background_pixmap = None;
    windowAttribs.border_pixel      = 0;
    windowAttribs.event_mask        = StructureNotifyMask;
    windowAttribs.colormap          = m_colorMap;

    m_window = XCreateWindow(m_display, RootWindow(m_display, vi->screen),
                             0, 0, 100, 100, 0, vi->depth, InputOutput,
                             vi->visual,
                             CWBorderPixel|CWColormap|CWEventMask, &windowAttribs);
    if (!m_window)
    {
        log().log() << "Failed to create window.\n";
        return;
    }

    XFree(vi);

    XStoreName(m_display, m_window, "GL 3.0 Window");
    XMapWindow(m_display, m_window);

    const char* str = glXQueryServerString(m_display, DefaultScreen(m_display), GLX_VENDOR);
    if (!str) str = "";
    log().log() << "GLX_VENDOR server: " << str << "\n";

    str = glXQueryServerString(m_display, DefaultScreen(m_display), GLX_VERSION);
    if (!str) str = "";
    log().log() << "GLX_VERSION server: " << str << "\n";

    str = glXQueryServerString(m_display, DefaultScreen(m_display), GLX_EXTENSIONS);
    if (!str) str = "";
    log().log() << "GLX_EXTENSIONS server: " << str << "\n";

    str = glXQueryExtensionsString(m_display, DefaultScreen(m_display));
    if (!str) str = "";
    log().log() << "GLX_EXTENSIONS: " << str << "\n";

    str = glXGetClientString(m_display, GLX_VENDOR);
    if (!str) str = "";
    log().log() << "GLX_VENDOR client: " << str << "\n";

    str = glXGetClientString(m_display, GLX_VERSION);
    if (!str) str = "";
    log().log() << "GLX_VERSION client: " << str << "\n";

    str = glXGetClientString(m_display, GLX_EXTENSIONS);
    if (!str) str = "";
    log().log() << "GLX_EXTENSIONS client: " << str << "\n";

    m_glxCtx = glXCreateNewContext(m_display, fbconfig, GLX_RGBA_TYPE, 0, True);
    XSync(m_display, False);
    if (!glXIsDirect(m_display, m_glxCtx))
    {
        log().log() << "Indirect GLX rendering context obtained\n";
    }
    else
    {
        log().log() << "Direct GLX rendering context obtained\n";
    }
    glXMakeCurrent(m_display, m_window, m_glxCtx);

    XSelectInput(m_display, m_window, ExposureMask | KeyPressMask);

    m_wmDeleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(m_display, m_window, &m_wmDeleteMessage, 1);

    //XGrabKeyboard(m_display, m_window, True, GrabModeAsync, GrabModeAsync, CurrentTime);
}
////////////////////////////////////////////////////////////////////////////////
PluginWindowContextXlib::~PluginWindowContextXlib()
{
    log().log() << "PluginWindowContextXlib stop...\n";

    if (m_display)
    {
        //XUngrabKeyboard(m_display, CurrentTime);
        if (m_glxCtx)
        {
            glXMakeCurrent(m_display, 0, nullptr);
            glXDestroyContext(m_display, m_glxCtx);
        }
        if (m_window)
        {
            XDestroyWindow(m_display, m_window);
        }
        XFreeColormap(m_display, m_colorMap);
        XCloseDisplay(m_display);
    }
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextXlib::createContext(GfxContextType type)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void PluginWindowContextXlib::update()
{
    XEvent e;
    while (XPending(m_display) > 0)
    {
        XNextEvent(m_display, &e);
        switch (e.type)
        {
        case DestroyNotify:
            break;
        case ClientMessage:
            if (e.xclient.data.l[0] == static_cast<long>(m_wmDeleteMessage))
                if (m_closeCallback)
                    m_closeCallback();
            break;
        default:
            log().log() << e.type << std::endl;
            break;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextXlib::setResolution(uint32_t x, uint32_t y)
{
    WindowPlugin::setResolution(x, y);
    if (m_display && m_window)
    {
        XResizeWindow(m_display, m_window, x, y);
        return true;
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextXlib::setPosition(uint32_t x, uint32_t y)
{
    WindowPlugin::setPosition(x, y);
    if (m_display && m_window)
    {
        XMoveWindow(m_display, m_window, x, y);
        return true;
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextXlib::setTitle(const std::string& title)
{
    WindowPlugin::setTitle(title);
    if (m_display && m_window)
    {
        XStoreName(m_display, m_window, title.c_str());
        return true;
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
void PluginWindowContextXlib::swapBuffers()
{
    glXSwapBuffers(m_display, m_window);
}
////////////////////////////////////////////////////////////////////////////////
uint32_t PluginWindowContextXlib::getWindowId() const
{
    return m_window;
}
////////////////////////////////////////////////////////////////////////////////
