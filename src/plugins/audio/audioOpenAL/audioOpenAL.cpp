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
    : Library(engine), m_device(nullptr), m_context(nullptr)
{
    log().log() << "PluginAudioOpenAL start..." << std::endl;

    ALboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration)
    {
        log().log() << "ALC_ENUMERATION_EXT available" << std::endl;
    }

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

        if (m_device)
        {
            m_context = alcCreateContext(m_device, NULL);

            if (m_context)
            {
                alcMakeContextCurrent(m_context);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
PluginAudioOpenAL::~PluginAudioOpenAL()
{
    log().log() << "PluginAudioOpenAL stop..." << std::endl;

    alcMakeContextCurrent(NULL);
    if (m_context)
    {
        alcDestroyContext(m_context);
        m_context = nullptr;
    }
    if (m_device)
    {
        alcCloseDevice(m_device);
        m_device = nullptr;
    }
}
////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> PluginAudioOpenAL::listDevices() const
{
    const ALCchar *devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    const ALCchar *device = devices;
    size_t len = 0;
    std::vector<std::string> res;
    while (device && *device != '\0' && (device + 1) && *(device + 1) != '\0')
    {
        res.push_back(device);
        len = res.back().length();
        device += (len + 1);
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
