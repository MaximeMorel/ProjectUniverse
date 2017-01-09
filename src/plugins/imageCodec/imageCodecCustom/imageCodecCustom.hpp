#ifndef __IMAGECODECCUSTOM_HPP__
#define __IMAGECODECCUSTOM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/codecs/imageCodec.hpp"
#include "core/coretypes/image.hpp"
#include "imagecodeccustom_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECCUSTOM_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECCUSTOM_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECCUSTOM_EXPORT void closeLibInstance();
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
#endif // __IMAGECODECCUSTOM_HPP__
