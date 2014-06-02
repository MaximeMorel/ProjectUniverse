#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
class Texture : public Resource
{
public:
    Texture();
    virtual ~Texture() override;

private:
    GLuint m_bufferId;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __TEXTURE_HPP__