#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include "core/math/vec4.hpp"
#include "core/log/logger.hpp"
#include "core/engine_export.h"
#include <vector>
#include <atomic>
////////////////////////////////////////////////////////////////////////////////
class Image;
using ImagePtr = std::shared_ptr<Image>;
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT Image : public ResourceFile
{
public:
    enum Type : uint8_t
    {
        GRAY8,
        GRAYFP32,
        RGB8,
        RGBA8,
        RGBFP32,
        RGBAFP32,
        RGBADXT1,
        UNKNOWN
    };

    struct Info
    {
        Info();

        Vec2ui resolution;            ///< image resolution
        uint8_t channels;             ///< number of channels
        uint8_t bpc;                  ///< bits per channel component
        uint8_t nummipmaps;           ///< number of mipmaps levels, at least 1, all the levels are stored in the same contiguous buffer
        Type type;                    ///< image type
    };

    Image(const std::string& name, const std::string& fileName);
    virtual ~Image() override;

    static ImagePtr create(const std::string& name, const std::string& fileName);

    /// Save image to file
    bool save(const std::string& filePath);

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

    /// Get image info structure
    const Info imageInfo() const;

     /// Get type of image (GRAY, RGB, RGBA, ...)
    void setImageType(Type type);

    /// Resize image. Set number of channels and bits per component before, use setImageType
    void resize(uint32_t w, uint32_t h);

    /// pixel and component access functions
    uint8_t* getui8(uint32_t x, uint32_t y);
    float& getfp32(uint32_t x, uint32_t y);
    Vec3ui8 get3ui8(uint32_t x, uint32_t y);
    Vec4ui8 get4ui8(uint32_t x, uint32_t y);

    virtual bool reload() override;

    bool asyncLoadStatus()
    {
        return m_asyncLoadStatus;
    }

protected:
    std::vector<uint8_t> m_buffer;  ///< buffer containing image data
    Info m_info;                    ///< struct holding resolution, channels, bpp, type, compression

public:
    std::atomic<bool> m_asyncLoadStatus;

private:
    using super = ResourceFile;

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGE_HPP__
