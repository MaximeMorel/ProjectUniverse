////////////////////////////////////////////////////////////////////////////////
#include "opengltools.hpp"
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
void glFlushErrors()
{
    int i = 0;
    GLenum err = glGetError();
    while (err != GL_NO_ERROR)
    {
        if (i > 1000)
            break;
        err = glGetError();
        ++i;
    }
}
////////////////////////////////////////////////////////////////////////////////
const char* glGetErrorString(GLenum err)
{
    switch (err)
    {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    case GL_TABLE_TOO_LARGE:
        return "GL_TABLE_TOO_LARGE";
    }
    return "GL_UNKNOWN_ERROR";
}
////////////////////////////////////////////////////////////////////////////////
void glLogCurrentError()
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        log().log() << glGetErrorString(err) << "\n";
}
////////////////////////////////////////////////////////////////////////////////
