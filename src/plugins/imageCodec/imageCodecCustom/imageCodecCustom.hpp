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

    virtual bool load(Image* image) override;
    virtual bool save(Image* image, const std::string& filePath) override;

private:
    bool loadPBM(Image* image);
    bool loadPGM(Image* image);
    bool loadPPM(Image* image);
    bool loadDDS(Image* image);

    bool savePBM(Image* image, const std::string& filePath);
    bool savePGM(Image* image, const std::string& filePath);
    bool savePPM(Image* image, const std::string& filePath);
    bool saveDDS(Image* image, const std::string& filePath);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGECODECCUSTOM_HPP__
