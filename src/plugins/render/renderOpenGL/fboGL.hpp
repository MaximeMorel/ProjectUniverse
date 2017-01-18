#ifndef __FBO_OPENGL_HPP__
#define __FBO_OPENGL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "glObject.hpp"
#include "GL/glew.h"
////////////////////////////////////////////////////////////////////////////////
class FBOGL : public OpenGLObject
{
public:
    FBOGL();
    virtual ~FBOGL() override;

    bool init();

    GLuint getFboId() const;

protected:
    GLuint m_fboId;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __FBO_OPENGL_HPP__
