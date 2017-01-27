////////////////////////////////////////////////////////////////////////////////
#include "config.hpp"
////////////////////////////////////////////////////////////////////////////////
Config* gConfig = nullptr;
////////////////////////////////////////////////////////////////////////////////
template <typename T>
Type getType();
////////////////////////////////////////////////////////////////////////////////
template <>
Type getType<bool>()
{
    return Type::BOOL;
}
////////////////////////////////////////////////////////////////////////////////
template <>
Type getType<int>()
{
    return Type::INT;
}
////////////////////////////////////////////////////////////////////////////////
template <>
Type getType<std::string>()
{
    return Type::STRING;
}
////////////////////////////////////////////////////////////////////////////////
template <>
Type getType<Vec2i>()
{
    return Type::VEC2I;
}
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
Type ConfigEntry::getType() const
{
    return m_type;
}
////////////////////////////////////////////////////////////////////////////////
const std::string& ConfigEntry::getName() const
{
    return m_name;
}
////////////////////////////////////////////////////////////////////////////////
void ConfigEntry::set(const std::string& value)
{
}
////////////////////////////////////////////////////////////////////////////////
void ConfigEntry::setString(const std::string& value)
{
}
////////////////////////////////////////////////////////////////////////////////
void ConfigEntry::setInt(int value)
{
}
////////////////////////////////////////////////////////////////////////////////
void ConfigEntry::setBool(bool value)
{
}
////////////////////////////////////////////////////////////////////////////////
void ConfigEntry::setFloat(float value)
{
}
////////////////////////////////////////////////////////////////////////////////
std::string ConfigEntry::getAsString() const
{
    return "";
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TConfigEntry<T>::TConfigEntry(const std::string& name, const T& data)
    : ConfigEntry(name, ::getType<T>())
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
void TConfigEntry<T>::set(const std::string& value)
{
}
////////////////////////////////////////////////////////////////////////////////
template <>
void TConfigEntry<int>::set(const std::string& value)
{
    m_data = std::stoi(value);
}
////////////////////////////////////////////////////////////////////////////////
template <>
void TConfigEntry<bool>::set(const std::string& value)
{
    m_data = std::stoi(value);
}
////////////////////////////////////////////////////////////////////////////////
template <>
void TConfigEntry<std::string>::set(const std::string& value)
{
    m_data = value;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TConfigEntry<T>::setString(const std::string& value)
{
    //m_data = value;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TConfigEntry<T>::setInt(int value)
{
    //m_data = value;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TConfigEntry<T>::setBool(bool value)
{
    //m_data = value;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TConfigEntry<T>::setFloat(float value)
{
    //m_data = value;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TConfigEntry<T>::setT(const T& data)
{
    m_data = data;
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
std::string TConfigEntry<std::string>::getAsString() const
{
    return m_data;
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
    if (entry && entry->getType() == getType<T>())
    {
        return (static_cast<const TConfigEntry<T>*>(entry))->get();
    }

    return T();
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void Config::set(const std::string& paramName, const T& value)
{
    ConfigEntry* entry = getEntry(paramName);
    if (entry && entry->getType() == getType<T>())
    {
        static_cast<TConfigEntry<T>*>(entry)->setT(value);
    }
}
////////////////////////////////////////////////////////////////////////////////
void Config::set(const std::string& paramName, const std::string& value)
{
    if (paramName.length() == 0)
        return;

    ConfigEntry* entry = getEntry(paramName);
    if (entry)
    {
        entry->set(value);
    }
}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const Config& config)
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
template class TConfigEntry<int>;
template class TConfigEntry<bool>;
template class TConfigEntry<std::string>;
template class TConfigEntry<Vec2i>;

template std::string Config::get<std::string>(const std::string& name) const;

template void Config::set<std::string>(const std::string& paramName, const std::string& value);
////////////////////////////////////////////////////////////////////////////////
