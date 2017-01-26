#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/log/logger.hpp"
#include <string>
#include <map>
////////////////////////////////////////////////////////////////////////////////
enum class Type : uint8_t
{
    BOOL,
    INT,
    STRING
};

class ConfigEntry;
template <typename T>
class TConfigEntry;

////////////////////////////////////////////////////////////////////////////////
class Config
{
public:
    Config();

    ~Config();

    void initDefaultConfig();

    const ConfigEntry* getC(const std::string& name) const;

    ConfigEntry* getC(const std::string& name);

    template <typename T>
    T get(const std::string& name) const;

    void set(const std::string& paramName, const std::string& value);

    friend Logger& operator<<(Logger& o, const Config& config);

    TConfigEntry<std::string>* app;
    TConfigEntry<std::string>* renderplugin;
    TConfigEntry<std::string>* inputplugin;
    TConfigEntry<std::string>* audioplugin;
    TConfigEntry<std::string>* windowplugin;
    TConfigEntry<std::string>* codecplugins;
    TConfigEntry<std::string>* resolution;
    TConfigEntry<std::string>* position;
    TConfigEntry<int>* windowmode;

private:
    std::map<std::string, ConfigEntry*> m_config;
};
////////////////////////////////////////////////////////////////////////////////
/// Global config access
void setGlobalConfig(Config& config);
Config& config();
////////////////////////////////////////////////////////////////////////////////
#endif // __CONFIG_HPP__
