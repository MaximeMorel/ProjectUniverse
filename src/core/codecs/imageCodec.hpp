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

    virtual bool load(ImagePtr image);
    virtual bool save(ImagePtr image, const std::string& filePath);
    virtual bool save(Image* image, const std::string& filePath);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGECODEC_HPP__
