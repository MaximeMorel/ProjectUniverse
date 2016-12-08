////////////////////////////////////////////////////////////////////////////////
#include "windowContextSDL2.hpp"
#include <SDL.h>
#include <GL/gl.h>
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
{
    log().log() << "PluginWindowContextSDL2 start...\n";

    if (SDL_WasInit(SDL_INIT_VIDEO))
    {
        log().log() << "SDL Video subsystem already started\n";
    }
    else
    {
        int ret = SDL_InitSubSystem(SDL_INIT_VIDEO);
        if (ret < 0)
        {
            log().log() << SDL_GetError();
        }
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    m_window = SDL_CreateWindow("SDL2 window",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                100, 100,
                                SDL_WINDOW_OPENGL);

    if (m_window == nullptr)
    {
        log().log() << SDL_GetError();
    }
    else
    {
        setTitle("title");
        //setResolution(Vec2i(640, 360));
        //setPosition(Vec2i(100, 100));

        // Create an OpenGL context associated with the window.
        m_glcontext = SDL_GL_CreateContext(m_window);

        checkAttributes();

        // now you can make GL calls.
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);

        swapBuffers();
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
bool PluginWindowContextSDL2::setResolution(Vec2i resolution)
{
    WindowPlugin::setResolution(resolution);
    if (m_window)
    {
        SDL_SetWindowSize(m_window, resolution.x, resolution.y);
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginWindowContextSDL2::setPosition(Vec2i position)
{
    WindowPlugin::setPosition(position);
    if (m_window)
    {
        SDL_SetWindowPosition(m_window, position.x, position.y);
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
void PluginWindowContextSDL2::checkAttributes()
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
}
////////////////////////////////////////////////////////////////////////////////
