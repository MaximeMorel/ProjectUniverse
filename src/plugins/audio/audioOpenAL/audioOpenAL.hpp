#ifndef __AUDIOOPENAL_HPP__
#define __AUDIOOPENAL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
////////////////////////////////////////////////////////////////////////////////
extern "C" PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginAudioOpenAL : public Library
{
public:
    PluginAudioOpenAL(Engine& engine);
    ~PluginAudioOpenAL();
};
////////////////////////////////////////////////////////////////////////////////
#endif // __AUDIOOPENAL_HPP__