#ifndef __VAO_OPENGL_HPP__
#define __VAO_OPENGL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "glObject.hpp"
#include "GL/glew.h"
////////////////////////////////////////////////////////////////////////////////
class VAOGL : public OpenGLObject
{
public:
    VAOGL();
    virtual ~VAOGL() override;

    bool init();

    GLuint getVaoId() const;

    virtual void bind();

protected:
    GLuint m_vaoId;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __VAO_OPENGL_HPP__
