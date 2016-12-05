#ifndef __OPENGL4TOOLS_HPP__
#define __OPENGL4TOOLS_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
void glFlushErrors();
const char* glGetErrorString(GLenum err);
void glLogCurrentError();
////////////////////////////////////////////////////////////////////////////////
#endif // __OPENGL4TOOLS_HPP__
