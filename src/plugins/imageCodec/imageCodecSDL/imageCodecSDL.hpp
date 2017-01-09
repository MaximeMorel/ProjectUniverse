#ifndef __IMAGECODECSDL_HPP__
#define __IMAGECODECSDL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/codecs/imageCodec.hpp"
#include "core/coretypes/image.hpp"
#include "imagecodecsdl_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECSDL_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECSDL_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECSDL_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginImageCodecCustom : public ImageCodec
{
public:
    PluginImageCodecCustom(Engine& engine);
    ~PluginImageCodecCustom() override;

    virtual bool load(ImagePtr image) override;
    virtual bool load(Image* image) override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGECODECSDL_HPP__
