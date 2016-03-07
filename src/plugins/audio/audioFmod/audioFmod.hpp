#ifndef __AUDIOFMOD_HPP__
#define __AUDIOFMOD_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
////////////////////////////////////////////////////////////////////////////////
extern "C" PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginAudioFmod : public Library
{
public:
    PluginAudioFmod(Engine& engine);
    ~PluginAudioFmod();
};
////////////////////////////////////////////////////////////////////////////////
#endif // __AUDIOFMOD_HPP__