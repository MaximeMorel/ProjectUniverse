////////////////////////////////////////////////////////////////////////////////
#include "audioOpenAL.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "audioOpenAL",
                          "audioOpenAL",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginAudioOpenAL* lib = nullptr;
////////////////////////////////////////////////////////////////////////////////
const PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Library* getLibInstance(Engine* engine)
{
    if (lib == nullptr)
    {
        lib = new PluginAudioOpenAL(*engine);
    }
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void closeLibInstance()
{
    delete lib;
    lib = nullptr;
}
////////////////////////////////////////////////////////////////////////////////
PluginAudioOpenAL::PluginAudioOpenAL(Engine &engine)
    : Library(engine), m_device(nullptr)
{
    log().log() << "PluginAudioOpenAL start..." << std::endl;

    std::vector<std::string> list = listDevices();
    if (!list.empty())
    {
        log().log() << "OpenAl devices:\n";
        for (const auto& str : list)
        {
            log().log() << str << "\n";
        }

        log().log() << "Using device: " << list[0].c_str() << std::endl;
        m_device = alcOpenDevice(list[0].c_str());
    }
}
////////////////////////////////////////////////////////////////////////////////
PluginAudioOpenAL::~PluginAudioOpenAL()
{
    log().log() << "PluginAudioOpenAL stop..." << std::endl;
    if (m_device)
    {
        alcCloseDevice(m_device);
    }
}
////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> PluginAudioOpenAL::listDevices() const
{
    const ALCchar *devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;
    std::vector<std::string> res;
    while (device && *device != '\0' && next && *next != '\0')
    {
        res.push_back(device);
        len = res.back().length();
        device += (len + 1);
        next += (len + 2);
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
