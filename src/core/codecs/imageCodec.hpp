#ifndef __IMAGECODEC_HPP__
#define __IMAGECODEC_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/codecs/codec.hpp"
#include "core/coretypes/image.hpp"
////////////////////////////////////////////////////////////////////////////////
class ImageCodec : public Codec
{
public:
    ImageCodec(Engine& engine);
    ~ImageCodec() override;

    virtual bool load(ImageRGBAPtr image);
    virtual bool save(ImageRGBAPtr image, const std::string& filePath);
    virtual bool save(ImageRGBA* image, const std::string& filePath);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGECODEC_HPP__
