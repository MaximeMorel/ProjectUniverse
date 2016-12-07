////////////////////////////////////////////////////////////////////////////////
#include "audioOpenAL.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "audioOpenAL",
                          "audioOpenAL",
                          "audio",
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
    log().log() << "PluginAudioOpenAL start...\n";

    m_device = alcOpenDevice(nullptr);
    if (m_device)
    {
        ALboolean enumeration = alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT");
        if (enumeration)
        {
            log().log() << "ALC_ENUMERATION_EXT available\n";
        }

        m_context = alcCreateContext(m_device, nullptr);
        if (m_context)
        {
            alcMakeContextCurrent(m_context);
        }

        std::vector<std::string> list = listDevices();
        if (!list.empty())
        {
            log().log() << "OpenAl devices:\n";
            uint8_t i = 0;
            for (const auto& str : list)
            {
                log().log() << i << " - " << str << "\n";
                ++i;
            }
        }
    }
    else
    {
        log().log() << "Cannot open OpenAL device\n";
    }

    getInfo();
}
////////////////////////////////////////////////////////////////////////////////
PluginAudioOpenAL::~PluginAudioOpenAL()
{
    log().log() << "PluginAudioOpenAL stop...\n";

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
    size_t len = 0;
    std::vector<std::string> res;
    while (devices && *devices != '\0' && (devices + 1) && *(devices + 1) != '\0')
    {
        res.push_back(devices);
        len = res.back().length();
        devices += (len + 1);
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
void PluginAudioOpenAL::getInfo()
{
    const ALchar* str = nullptr;

    str = alGetString(AL_VENDOR);
    log().log() << "AL_VENDOR: " << reinterpret_cast<const char*>(str) << "\n";
    str = alGetString(AL_VERSION);
    log().log() << "AL_VERSION: " << reinterpret_cast<const char*>(str) << "\n";
    str = alGetString(AL_RENDERER);
    log().log() << "AL_RENDERER: " << reinterpret_cast<const char*>(str) << "\n";
    str = alGetString(AL_EXTENSIONS);
    log().log() << "AL_EXTENSIONS: " << reinterpret_cast<const char*>(str) << "\n";

    str = alcGetString(m_device, ALC_DEFAULT_DEVICE_SPECIFIER);
    log().log() << "ALC_DEFAULT_DEVICE_SPECIFIER: " << reinterpret_cast<const char*>(str) << "\n";
    str = alcGetString(m_device, ALC_DEVICE_SPECIFIER);
    log().log() << "ALC_DEVICE_SPECIFIER: " << reinterpret_cast<const char*>(str) << "\n";
    str = alcGetString(m_device, ALC_EXTENSIONS);
    log().log() << "ALC_EXTENSIONS: " << reinterpret_cast<const char*>(str) << "\n";

    ALCint alcMajor = 0;
    ALCint alcMinor = 0;
    alcGetIntegerv(m_device, ALC_MAJOR_VERSION, 1, &alcMajor);
    alcGetIntegerv(m_device, ALC_MINOR_VERSION, 1, &alcMinor);
    log().log() << "ALC_VERSION: " << alcMajor << "." << alcMinor << "\n";
}
////////////////////////////////////////////////////////////////////////////////
