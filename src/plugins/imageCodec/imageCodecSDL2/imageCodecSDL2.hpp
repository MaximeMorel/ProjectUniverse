#ifndef __IMAGECODECSDL2_HPP__
#define __IMAGECODECSDL2_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/codecs/imageCodec.hpp"
#include "core/coretypes/image.hpp"
#include "imagecodecsdl2_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECSDL2_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECSDL2_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" IMAGECODECSDL2_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginImageCodecSDL2 : public ImageCodec
{
public:
    PluginImageCodecSDL2(Engine& engine);
    ~PluginImageCodecSDL2() override;

    virtual bool load(Image* image) override;
    virtual bool save(Image* image, const std::string& filePath) override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGECODECSDL2_HPP__
