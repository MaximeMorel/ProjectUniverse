////////////////////////////////////////////////////////////////////////////////
#include "windowContextSDL2.hpp"
#include "core/log/logManager.hpp"
#include <SDL.h>
#include <SDL_syswm.h>
#include <map>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "windowSDL",
                          "WindowSDL",
                          "window",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginWindowContextSDL2* lib = nullptr;
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
        lib = new PluginWindowContextSDL2(*engine);
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
PluginWindowContextSDL2::PluginWindowContextSDL2(Engine& engine)
    : WindowPlugin(engine)
    , m_window(nullptr)
    , m_glcontext(nullptr)
{
    log().log() << "PluginWindowContextSDL2 start...\n";

    int ret = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        log().log() << SDL_GetError();
    }
    else if (ret == 0)
    {
        log().log() << "SDL_INIT_VIDEO success.\n";
    }
}
////////////////////////////////////////////////////////////////////////////////
PluginWindowContextSDL2::~PluginWindowContextSDL2()
{
    log().log() << "PluginWindowContextSDL2 stop...\n";

    SDL_GL_DeleteContext(m_glcontext);

    SDL_DestroyWindow(m_window);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
    log().log() << SDL_GetError();
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::createContext(GfxContextType type)
{
    switch (type)
    {
    case GfxContextType::OPENGL_2_1:
        return createContextOpenGL21();
    case GfxContextType::OPENGL_3_3:
        return createContextOpenGL33();
    case GfxContextType::OPENGL_4_5:
        return createContextOpenGL45();
    case GfxContextType::VULKAN:
        return createContextVulkan();
    default:
        break;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void PluginWindowContextSDL2::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            if (m_closeCallback)
                m_closeCallback();
            break;
        case SDL_WINDOWEVENT:
            break;
        case SDL_SYSWMEVENT:
            break;
        default:
            m_pushedEvents.push_back(event);
            break;
        }
    }

    for (auto& ev : m_pushedEvents)
    {
        SDL_PushEvent(&ev);
    }
    m_pushedEvents.clear();
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::setResolution(uint32_t x, uint32_t y)
{
    WindowPlugin::setResolution(x, y);
    if (m_window)
    {
        SDL_SetWindowSize(m_window, x, y);
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::setPosition(uint32_t x, uint32_t y)
{
    WindowPlugin::setPosition(x, y);
    if (m_window)
    {
        SDL_SetWindowPosition(m_window, x, y);
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::setTitle(const std::string& title)
{
    WindowPlugin::setTitle(title);
    if (m_window)
    {
        SDL_SetWindowTitle(m_window, title.c_str());
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void PluginWindowContextSDL2::swapBuffers()
{
    SDL_GL_SwapWindow(m_window);
}
////////////////////////////////////////////////////////////////////////////////
uint32_t PluginWindowContextSDL2::getWindowId() const
{
    if (m_window)
    {
        SDL_SysWMinfo info;
        SDL_VERSION(&info.version);
        SDL_GetWindowWMInfo(m_window, &info);
        switch (info.subsystem)
        {
        #ifdef SDL_VIDEO_DRIVER_X11
        case SDL_SYSWM_X11:
            return info.info.x11.window;
        #endif // SDL_VIDEO_DRIVER_X11
        #ifdef SDL_VIDEO_DRIVER_WAYLAND
        case SDL_SYSWM_WAYLAND:
            //return info.info.wl.surface;
        #endif // SDL_VIDEO_DRIVER_WAYLAND
        #ifdef SDL_VIDEO_DRIVER_WINDOWS
        case SDL_SYSWM_WINDOWS:
            return info.info.win.window;
        #endif // SDL_VIDEO_DRIVER_WINDOWS
        case SDL_SYSWM_ANDROID:
        case SDL_SYSWM_DIRECTFB:
        case SDL_SYSWM_COCOA:
        case SDL_SYSWM_UIKIT:
        case SDL_SYSWM_MIR:
        case SDL_SYSWM_WINRT:
        case SDL_SYSWM_UNKNOWN:
        default:
            break;
        }
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
void PluginWindowContextSDL2::logAttributes()
{
    std::map<SDL_GLattr, std::string> attributes = {{SDL_GL_RED_SIZE, "SDL_GL_RED_SIZE"},
                                                    {SDL_GL_GREEN_SIZE, "SDL_GL_GREEN_SIZE"},
                                                    {SDL_GL_BLUE_SIZE, "SDL_GL_BLUE_SIZE"},
                                                    {SDL_GL_ALPHA_SIZE, "SDL_GL_ALPHA_SIZE"},
                                                    {SDL_GL_BUFFER_SIZE, "SDL_GL_BUFFER_SIZE"},
                                                    {SDL_GL_DOUBLEBUFFER, "SDL_GL_DOUBLEBUFFER"},
                                                    {SDL_GL_DEPTH_SIZE, "SDL_GL_DEPTH_SIZE"},
                                                    {SDL_GL_STENCIL_SIZE, "SDL_GL_STENCIL_SIZE"},
                                                    {SDL_GL_ACCUM_RED_SIZE, "SDL_GL_ACCUM_RED_SIZE"},
                                                    {SDL_GL_ACCUM_GREEN_SIZE, "SDL_GL_ACCUM_GREEN_SIZE"},
                                                    {SDL_GL_ACCUM_BLUE_SIZE, "SDL_GL_ACCUM_BLUE_SIZE"},
                                                    {SDL_GL_ACCUM_ALPHA_SIZE, "SDL_GL_ACCUM_ALPHA_SIZE"},
                                                    {SDL_GL_STEREO, "SDL_GL_STEREO"},
                                                    {SDL_GL_MULTISAMPLEBUFFERS, "SDL_GL_MULTISAMPLEBUFFERS"},
                                                    {SDL_GL_MULTISAMPLESAMPLES, "SDL_GL_MULTISAMPLESAMPLES"},
                                                    {SDL_GL_ACCELERATED_VISUAL, "SDL_GL_ACCELERATED_VISUAL"},
                                                    {SDL_GL_RETAINED_BACKING, "SDL_GL_RETAINED_BACKING"},
                                                    {SDL_GL_CONTEXT_MAJOR_VERSION, "SDL_GL_CONTEXT_MAJOR_VERSION"},
                                                    {SDL_GL_CONTEXT_MINOR_VERSION, "SDL_GL_CONTEXT_MINOR_VERSION"},
                                                    {SDL_GL_CONTEXT_EGL, "SDL_GL_CONTEXT_EGL"},
                                                    {SDL_GL_CONTEXT_FLAGS, "SDL_GL_CONTEXT_FLAGS"},
                                                    {SDL_GL_CONTEXT_PROFILE_MASK, "SDL_GL_CONTEXT_PROFILE_MASK"},
                                                    {SDL_GL_SHARE_WITH_CURRENT_CONTEXT, "SDL_GL_SHARE_WITH_CURRENT_CONTEXT"},
                                                    {SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, "SDL_GL_FRAMEBUFFER_SRGB_CAPABLE"},
                                                    {SDL_GL_CONTEXT_RELEASE_BEHAVIOR, "SDL_GL_CONTEXT_RELEASE_BEHAVIOR"}};

    for (const auto& attr : attributes)
    {
        int v = 0;
        SDL_GL_GetAttribute(attr.first, &v);
        log().log() << attr.second << ": " << v << "\n";
    }

    log().log() << "SDL window driver: " << SDL_GetCurrentVideoDriver() << "\n";
    int numDpy = SDL_GetNumVideoDisplays();
    log().log() << "SDL num displays: " << numDpy << "\n";
    if (numDpy > 0)
    {
        SDL_DisplayMode mode;
        SDL_GetCurrentDisplayMode(0, &mode);
        log().log() << "SDL display mode: " << mode.w << "x" << mode.h << " " << mode.refresh_rate << " Hz" << std::endl;
    }
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::createContextOpenGL21()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    return createWindow(SDL_WINDOW_OPENGL);
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::createContextOpenGL33()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    return createWindow(SDL_WINDOW_OPENGL);
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::createContextOpenGL45()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    return createWindow(SDL_WINDOW_OPENGL);
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::createContextVulkan()
{
    return createWindow(SDL_WINDOW_SHOWN);
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::createWindow(SDL_WindowFlags flags)
{
    m_window = SDL_CreateWindow("SDL2 window",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                100, 100,
                                flags);

    if (m_window == nullptr)
    {
        log().log() << SDL_GetError();
        return false;
    }

    if (flags & SDL_WINDOW_OPENGL)
    {
        // Create an OpenGL context associated with the window.
        m_glcontext = SDL_GL_CreateContext(m_window);
        if (m_glcontext == nullptr)
        {
            log().log() << SDL_GetError();
            return false;
        }
    }

    logAttributes();

    return true;
}
////////////////////////////////////////////////////////////////////////////////
