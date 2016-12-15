#ifndef __IMAGECODECJPEG_HPP__
#define __IMAGECODECJPEG_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/codecs/imageCodec.hpp"
#include "core/coretypes/image.hpp"
#include "imagecodecjpeg_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECJPEG_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECJPEG_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECJPEG_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginImageCodecJPEG : public ImageCodec
{
public:
    PluginImageCodecJPEG(Engine& engine);
    ~PluginImageCodecJPEG() override;

    virtual bool load(ImageRGBAPtr image) override;
    virtual bool save(ImageRGBAPtr image, const std::string& filePath) override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGECODECJPEG_HPP__
