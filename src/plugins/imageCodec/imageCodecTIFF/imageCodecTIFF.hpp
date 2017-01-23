#ifndef __IMAGECODECTIFF_HPP__
#define __IMAGECODECTIFF_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/codecs/imageCodec.hpp"
#include "core/coretypes/image.hpp"
#include "imagecodectiff_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECTIFF_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECTIFF_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECTIFF_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginImageCodecTIFF : public ImageCodec
{
public:
    PluginImageCodecTIFF(Engine& engine);
    ~PluginImageCodecTIFF() override;

    virtual bool load(Image* image) override;
    virtual bool save(Image* image, const std::string& filePath) override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGECODECTIFF_HPP__
