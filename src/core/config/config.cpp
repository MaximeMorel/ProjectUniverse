////////////////////////////////////////////////////////////////////////////////
#include "config.hpp"
////////////////////////////////////////////////////////////////////////////////
Config* gConfig = nullptr;
////////////////////////////////////////////////////////////////////////////////
template <typename T>
ConfigEntry::Type getConfigEntryType();
////////////////////////////////////////////////////////////////////////////////
template <>
ConfigEntry::Type getConfigEntryType<bool>()
{
    return ConfigEntry::Type::BOOL;
}
////////////////////////////////////////////////////////////////////////////////
template <>
ConfigEntry::Type getConfigEntryType<int>()
{
    return ConfigEntry::Type::INT;
}
////////////////////////////////////////////////////////////////////////////////
template <>
ConfigEntry::Type getConfigEntryType<std::string>()
{
    return ConfigEntry::Type::STRING;
}
////////////////////////////////////////////////////////////////////////////////
template <>
ConfigEntry::Type getConfigEntryType<Vec2i>()
{
    return ConfigEntry::Type::VEC2I;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ConfigEntry::ConfigEntry(const std::string& name, Type t)
    : m_type(t)
    , m_name(name)
{
}
////////////////////////////////////////////////////////////////////////////////
ConfigEntry::~ConfigEntry()
{
}
////////////////////////////////////////////////////////////////////////////////
ConfigEntry::Type ConfigEntry::getType() const
{
    return m_type;
}
////////////////////////////////////////////////////////////////////////////////
const std::string& ConfigEntry::getName() const
{
    return m_name;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TConfigEntry<T>::TConfigEntry(const std::string& name, const T& data)
    : ConfigEntry(name, getConfigEntryType<T>())
    , m_data(data)
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TConfigEntry<T>::~TConfigEntry()
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool TConfigEntry<T>::set(const T& data)
{
    m_data = data;
    return true;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool TConfigEntry<T>::setFromString(const std::string& value)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
template <>
bool TConfigEntry<bool>::setFromString(const std::string& value)
{
    if (value == "true")
    {
        m_data = true;
        return true;
    }
    if (value == "false")
    {
        m_data = false;
        return true;
    }
    int v = std::stoi(value);
    m_data = v;
    return true;
}
////////////////////////////////////////////////////////////////////////////////
template <>
bool TConfigEntry<int>::setFromString(const std::string& value)
{
    int v = std::stoi(value);
    m_data = v;
    return true;
}
////////////////////////////////////////////////////////////////////////////////
template <>
bool TConfigEntry<std::string>::setFromString(const std::string& value)
{
    m_data = value;
    return true;
}
////////////////////////////////////////////////////////////////////////////////
template <>
bool TConfigEntry<Vec2i>::setFromString(const std::string& value)
{
    size_t pos = value.find(',');
    if (pos == std::string::npos)
        return false;
    m_data.x = std::stoi(value.substr(0, pos));
    m_data.y = std::stoi(value.substr(pos + 1));
    return true;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T TConfigEntry<T>::get() const
{
    return m_data;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string TConfigEntry<T>::getAsString() const
{
    return "";
}
////////////////////////////////////////////////////////////////////////////////
template <>
std::string TConfigEntry<int>::getAsString() const
{
    return std::to_string(m_data);
}
////////////////////////////////////////////////////////////////////////////////
template <>
std::string TConfigEntry<bool>::getAsString() const
{
    return std::to_string(m_data);
}
////////////////////////////////////////////////////////////////////////////////
template <>
std::string TConfigEntry<std::string>::getAsString() const
{
    return m_data;
}
////////////////////////////////////////////////////////////////////////////////
template <>
std::string TConfigEntry<Vec2i>::getAsString() const
{
    return std::to_string(m_data.x) + "," + std::to_string(m_data.y);
}
////////////////////////////////////////////////////////////////////////////////
Config::Config()
    : app(nullptr)
    , renderplugin(nullptr)
    , inputplugin(nullptr)
    , audioplugin(nullptr)
    , windowplugin(nullptr)
    , codecplugins(nullptr)
    , resolution(nullptr)
    , position(nullptr)
    , fullscreen(nullptr)
    , borderless(nullptr)
{
}
////////////////////////////////////////////////////////////////////////////////
Config::~Config()
{
    for (auto configEntry : m_config)
    {
        delete configEntry.second;
    }
}
////////////////////////////////////////////////////////////////////////////////
void Config::initDefaultConfig()
{
    if (!app)
        app = new TConfigEntry<std::string>("app", "dummy");
    m_config["app"] = app;

    if (!resolution)
        resolution = new TConfigEntry<Vec2i>("resolution", Vec2i(100, 100));
    m_config["resolution"] = resolution;

    if (!position)
        position = new TConfigEntry<Vec2i>("position", Vec2i(0, 0));
    m_config["position"] = position;

    if (!fullscreen)
        fullscreen = new TConfigEntry<bool>("fullscreen", false);
    m_config["fullscreen"] = fullscreen;

    if (!borderless)
        borderless = new TConfigEntry<bool>("borderless", false);
    m_config["borderless"] = borderless;

    if (!renderplugin)
        renderplugin = new TConfigEntry<std::string>("renderplugin", "RenderOpenGL21");
    m_config["renderplugin"] = renderplugin;

    if (!inputplugin)
        inputplugin = new TConfigEntry<std::string>("inputplugin", "InputSDL");
    m_config["inputplugin"] = inputplugin;

    if (!audioplugin)
        audioplugin = new TConfigEntry<std::string>("audioplugin", "AudioOpenAL");
    m_config["audioplugin"] = audioplugin;

    if (!windowplugin)
        windowplugin = new TConfigEntry<std::string>("windowplugin", "WindowContextSDL2");
    m_config["windowplugin"] = windowplugin;

    if (!codecplugins)
        codecplugins = new TConfigEntry<std::string>("codecplugins", "ImageCodecJPEG,ImageCodecPNG,ImageCodecTIFF,ImageCodecCustom,ImageCodecSDL,MeshCodecCustom,MeshCodecASSIMP");
    m_config["codecplugins"] = codecplugins;
}
////////////////////////////////////////////////////////////////////////////////
void Config::checkConfig()
{

}
////////////////////////////////////////////////////////////////////////////////
const ConfigEntry* Config::getEntry(const std::string& paramName) const
{
    auto it = m_config.find(paramName);
    if (it != m_config.end())
    {
        return it->second;
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
ConfigEntry* Config::getEntry(const std::string& paramName)
{
    return const_cast<ConfigEntry*>(static_cast<const Config &>(*this).getEntry(paramName));
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T Config::get(const std::string& paramName) const
{
    const ConfigEntry* entry = getEntry(paramName);
    if (entry && entry->getType() == getConfigEntryType<T>())
    {
        return (static_cast<const TConfigEntry<T>*>(entry))->get();
    }

    return T();
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool Config::set(const std::string& paramName, const T& value)
{
    ConfigEntry* entry = getEntry(paramName);
    if (entry && entry->getType() == getConfigEntryType<T>())
    {
        return static_cast<TConfigEntry<T>*>(entry)->set(value);
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool Config::setFromString(const std::string& paramName, const std::string& value)
{
    if (paramName.length() == 0)
        return false;

    ConfigEntry* entry = getEntry(paramName);
    if (entry)
    {
        return entry->setFromString(value);
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
Logger ENGINE_EXPORT & operator<<(Logger& o, const Config& config)
{
    for (auto configEntry : config.m_config)
    {
        o << configEntry.first << "=" << configEntry.second->getAsString() << "\n";
    }
    return o;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void setGlobalConfig(Config& config)
{
    gConfig = &config;
}
////////////////////////////////////////////////////////////////////////////////
Config& config()
{
    return *gConfig;
}
////////////////////////////////////////////////////////////////////////////////
template class ENGINE_EXPORT TConfigEntry<int>;
template class ENGINE_EXPORT TConfigEntry<bool>;
template class ENGINE_EXPORT TConfigEntry<std::string>;
template class ENGINE_EXPORT TConfigEntry<Vec2i>;

template int Config::get<int>(const std::string& paramName) const;
template bool Config::get<bool>(const std::string& paramName) const;
template std::string Config::get<std::string>(const std::string& paramName) const;
template Vec2i Config::get<Vec2i>(const std::string& paramName) const;

template bool Config::set<int>(const std::string& paramName, const int& value);
template bool Config::set<bool>(const std::string& paramName, const bool& value);
template bool Config::set<std::string>(const std::string& paramName, const std::string& value);
template bool Config::set<Vec2i>(const std::string& paramName, const Vec2i& value);
////////////////////////////////////////////////////////////////////////////////
