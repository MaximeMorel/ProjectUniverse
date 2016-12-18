#ifndef __TEXTURE_OPENGL4_HPP__
#define __TEXTURE_OPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/texture.hpp"
////////////////////////////////////////////////////////////////////////////////
class TextureGL4 : public Texture
{
public:
    TextureGL4(const std::string& name, const std::string& fileName);
    virtual ~TextureGL4() override;

    static TexturePtr create(const std::string& name, const std::string& fileName);

    virtual void bind() override;
    virtual void unbind() override;

    virtual void setImage(ImagePtr image) override;

    virtual void reload() override;

private:
};
////////////////////////////////////////////////////////////////////////////////
#endif // __TEXTURE_OPENGL4_HPP__
