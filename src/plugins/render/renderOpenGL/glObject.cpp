////////////////////////////////////////////////////////////////////////////////
#include "glObject.hpp"
////////////////////////////////////////////////////////////////////////////////
OpenGLObject::OpenGLObject()
{
}
////////////////////////////////////////////////////////////////////////////////
OpenGLObject::~OpenGLObject()
{
}
////////////////////////////////////////////////////////////////////////////////
void OpenGLObject::printOn(Logger& o) const
{
}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const OpenGLObject& object)
{
    object.printOn(o);
    return o;
}
////////////////////////////////////////////////////////////////////////////////