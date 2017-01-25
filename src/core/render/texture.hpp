#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
#include "core/coretypes/image.hpp"
#include <atomic>
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
    virtual void bind(uint32_t unit);

    /// Unbind / deactivate the texture
    virtual void unbind();

    virtual uint32_t getUnit() const;

    virtual void setImage(ImagePtr image);

protected:
    virtual void printOn(Logger& o) const override;

protected:
    uint32_t m_textureId;
    uint32_t m_textureUnit;
    ImagePtr m_image;

    std::atomic<bool> m_setImagePending;

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __TEXTURE_HPP__
