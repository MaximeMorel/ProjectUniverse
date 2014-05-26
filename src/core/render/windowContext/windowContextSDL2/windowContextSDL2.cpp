////////////////////////////////////////////////////////////////////////////////
#include "windowContextSDL2.hpp"
////////////////////////////////////////////////////////////////////////////////
#include <SDL.h>
#include <GL/gl.h>
////////////////////////////////////////////////////////////////////////////////
WindowContextSDL2::WindowContextSDL2()
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
