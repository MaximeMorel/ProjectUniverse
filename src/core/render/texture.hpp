#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
#include "core/coretypes/image.hpp"
////////////////////////////////////////////////////////////////////////////////
class Texture;
using TexturePtr = std::shared_ptr<Texture>;
////////////////////////////////////////////////////////////////////////////////
class Texture : public ResourceFile
{
public:
    Texture(const std::string& name, const std::string& fileName);
    virtual ~Texture() override;

    static TexturePtr create(const std::string& name, const std::string& fileName);

    /// Get internal shader handle id
    uint32_t getTextureId() const;

    /// Bind / activate the texture
    virtual void bind();

    /// Unbind / deactivate the texture
    virtual void unbind();

    virtual void setImage(ImageRGBAPtr image);

protected:
    virtual void printOn(Logger& o) const override;

protected:
    uint32_t m_textureId;
    ImageRGBAPtr m_image;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __TEXTURE_HPP__
