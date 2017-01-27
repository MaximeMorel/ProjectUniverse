#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
#include <atomic>
////////////////////////////////////////////////////////////////////////////////
class Texture;
using TexturePtr = std::shared_ptr<Texture>;
////////////////////////////////////////////////////////////////////////////////
class Image;
using ImagePtr = std::shared_ptr<Image>;
////////////////////////////////////////////////////////////////////////////////
class Texture : public ResourceFile
{
public:
    Texture(const std::string& name, const std::string& fileName);
    virtual ~Texture() override;

    static TexturePtr create(const std::string& name, const std::string& fileName);

    /// Get internal texture handle id
    uint32_t getTextureId() const;

    /// Bind / activate the texture
    virtual void bind(uint32_t unit);

    /// Unbind / deactivate the texture
    virtual void unbind();

    virtual uint32_t getUnit() const;

    virtual void setImage(ImagePtr image);

protected:
    virtual void printOn(Logger& o) const override;

protected:
    uint32_t m_textureId;       ///< texture opengl object id
    uint32_t m_textureUnit;     ///< texturing unit id
    ImagePtr m_image;           ///< supporting image if any

    std::atomic<bool> m_setImagePending;    ///< true when waiting for completion of image loading

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __TEXTURE_HPP__
