#ifndef __TEXTURE_OPENGL_HPP__
#define __TEXTURE_OPENGL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/texture.hpp"
#include "GL/glew.h"
////////////////////////////////////////////////////////////////////////////////
class TextureGL : public Texture
{
public:
    TextureGL(const std::string& name);
    TextureGL(const std::string& name, const std::string& fileName);
    virtual ~TextureGL() override;

    static TexturePtr create(const std::string& name);
    static TexturePtr create(const std::string& name, const std::string& fileName);

    virtual void makeDepth(uint32_t x, uint32_t y) override;

    /// Get internal texture handle id
    GLuint getTextureId() const;

    virtual void bind(uint32_t unit) override;
    virtual void unbind() override;

    virtual void setImage(ImagePtr image) override;

    virtual void resize(Vec2ui resolution) override;
    virtual void resize(Vec3ui resolution) override;

    virtual bool reload() override;

protected:
    virtual void printOn(Logger& o) const override;

private:
    GLuint m_textureId;
    GLint m_internalformat;
    GLenum m_format;
    GLenum m_type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __TEXTURE_OPENGL_HPP__
