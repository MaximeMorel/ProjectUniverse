#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
#include "buffer.hpp"
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include "core/math/vec4.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Image;
using ImagePtr = std::shared_ptr<Image>;
////////////////////////////////////////////////////////////////////////////////
class Image : public ResourceFile
{
public:
    enum Type
    {
        GRAY8,
        GRAYFP32,
        RGB8,
        RGBA8,
        RGBFP32,
        RGBAFP32,
        UNKNOWN
    };

    Image(const std::string& name, const std::string& fileName);
    virtual ~Image() override;

    static ImagePtr create(const std::string& name, const std::string& fileName);

    /// Save image to file
    virtual bool save(const std::string& filePath);

    /// Get the sub search path for this resource
    static const char* getSearchPath();

    /// Get image resolution
    Vec2ui resolution() const;

    /// Get image width
    uint32_t width() const;

    /// Get image height
    uint32_t height() const;

    /// Get num channel. Ex: 3 for RGB, 4 for RGBA
    uint8_t channels() const;

    /// Get num bits per component. Ex: classic RGB uses 8 bits components, so 24 bits per pixel
    uint8_t bitsPerComponent() const;

    /// Get num bits per Pixel. Ex: classic RGB uses 8 bits components, so 24 bits per pixel
    uint8_t bitsPerPixel() const;

    /// Get type of image (GRAY, RGB, RGBA, ...)
    Type imageType() const;

     /// Get type of image (GRAY, RGB, RGBA, ...)
    void setImageType(Type type);

    /// Resize image. Set number of channels and bits per component before, use setImageType
    void resize(uint32_t w, uint32_t h);

    /// pixel and component access functions
    uint8_t* getui8(uint32_t x, uint32_t y);
    float& getfp32(uint32_t x, uint32_t y);
    Vec3ui8 get3ui8(uint32_t x, uint32_t y);
    Vec4ui8 get4ui8(uint32_t x, uint32_t y);

    virtual void reload() override;

protected:
    std::vector<uint8_t> m_buffer;  ///< buffer containing image data
    Vec2ui m_resolution;            ///< image resolution
    uint8_t m_channels;             ///< number of channels
    uint8_t m_bpc;                  ///< bits per channel component

private:
    using super = ResourceFile;

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGE_HPP__
