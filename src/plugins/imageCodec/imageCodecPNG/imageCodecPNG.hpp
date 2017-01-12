#ifndef __IMAGECODECPNG_HPP__
#define __IMAGECODECPNG_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/codecs/imageCodec.hpp"
#include "core/coretypes/image.hpp"
#include "imagecodecpng_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECPNG_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECPNG_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECPNG_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginImageCodecPNG : public ImageCodec
{
public:
    PluginImageCodecPNG(Engine& engine);
    ~PluginImageCodecPNG() override;

    virtual bool load(Image* image) override;
    virtual bool save(Image* image, const std::string& filePath) override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGECODECPNG_HPP__
