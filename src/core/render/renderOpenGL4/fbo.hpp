#ifndef __FBO_HPP__
#define __FBO_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
class FBO : public Resource
{
public:
    FBO();
    virtual ~FBO() override;

private:
    GLuint m_bufferId;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __FBO_HPP__
