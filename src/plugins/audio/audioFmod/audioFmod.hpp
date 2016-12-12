#ifndef __AUDIOFMOD_HPP__
#define __AUDIOFMOD_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "audiofmod_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" AUDIOFMOD_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" AUDIOFMOD_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" AUDIOFMOD_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginAudioFmod : public Library
{
public:
    PluginAudioFmod(Engine& engine);
    virtual ~PluginAudioFmod() override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __AUDIOFMOD_HPP__
