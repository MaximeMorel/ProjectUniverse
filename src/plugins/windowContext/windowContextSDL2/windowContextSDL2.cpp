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
{
    SDL_Window *window = SDL_CreateWindow("SDL2 window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_OPENGL);

    // Create an OpenGL context associated with the window.
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    // now you can make GL calls.
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}
////////////////////////////////////////////////////////////////////////////////
