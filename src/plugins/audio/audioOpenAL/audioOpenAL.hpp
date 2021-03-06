#ifndef __AUDIOOPENAL_HPP__
#define __AUDIOOPENAL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include <vector>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>
#include "audioopenal_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" AUDIOOPENAL_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" AUDIOOPENAL_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" AUDIOOPENAL_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginAudioOpenAL : public Library
{
public:
    PluginAudioOpenAL(Engine& engine);
    virtual ~PluginAudioOpenAL() override;

    std::vector<std::string> listDevices() const;

    void getInfo();

    void update();

private:
    ALCdevice* m_device;
    ALCcontext* m_context;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __AUDIOOPENAL_HPP__
