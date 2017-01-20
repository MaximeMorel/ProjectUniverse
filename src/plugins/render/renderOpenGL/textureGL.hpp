#ifndef __TEXTURE_OPENGL_HPP__
#define __TEXTURE_OPENGL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/texture.hpp"
#include "GL/glew.h"
////////////////////////////////////////////////////////////////////////////////
class TextureGL : public Texture
{
public:
    TextureGL(const std::string& name, const std::string& fileName);
    virtual ~TextureGL() override;

    static TexturePtr create(const std::string& name, const std::string& fileName);

    virtual void bind() override;
    virtual void unbind() override;

    virtual void setImage(ImagePtr image) override;

    virtual bool reload() override;

private:
    //GLuint m_textureId;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __TEXTURE_OPENGL_HPP__
