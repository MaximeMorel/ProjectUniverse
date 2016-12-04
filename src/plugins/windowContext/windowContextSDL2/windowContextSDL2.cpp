////////////////////////////////////////////////////////////////////////////////
#include "windowContextSDL2.hpp"
#include <SDL.h>
#include <GL/gl.h>
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
    m_window = SDL_CreateWindow("SDL2 window",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                640, 480,
                                SDL_WINDOW_OPENGL);

    if (m_window == nullptr)
    {
        log().log() << SDL_GetError();
    }

    // Create an OpenGL context associated with the window.
    m_glcontext = SDL_GL_CreateContext(m_window);

    // now you can make GL calls.
    glClearColor(0,0,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    swapBuffers();
}
////////////////////////////////////////////////////////////////////////////////
PluginWindowContextSDL2::~PluginWindowContextSDL2()
{
    SDL_GL_DeleteContext(m_glcontext);

    SDL_DestroyWindow(m_window);
    log().log() << SDL_GetError();
}
////////////////////////////////////////////////////////////////////////////////
void PluginWindowContextSDL2::swapBuffers()
{
    SDL_GL_SwapWindow(m_window);
}
////////////////////////////////////////////////////////////////////////////////
