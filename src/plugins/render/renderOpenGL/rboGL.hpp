#ifndef __RBO_OPENGL_HPP__
#define __RBO_OPENGL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "glObject.hpp"
#include "GL/glew.h"
////////////////////////////////////////////////////////////////////////////////
class RBOGL : public OpenGLObject
{
public:
    RBOGL();
    virtual ~RBOGL() override;

    bool init();

    GLuint getRboId() const;

protected:
    GLuint m_rboId;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RBO_OPENGL_HPP__
