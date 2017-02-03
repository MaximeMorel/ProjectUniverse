#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/log/logger.hpp"
#include "core/math/vec2.hpp"
#include "core/engine_export.h"
#include <string>
#include <map>
////////////////////////////////////////////////////////////////////////////////
/// Class to hold a config entry (name and value and type)
class ENGINE_EXPORT ConfigEntry
{
public:
    enum class Type : uint8_t;

protected:
    ConfigEntry(const std::string& name, Type t);

public:
    virtual ~ConfigEntry();

    /// get template type of the underlying instance
    Type getType() const;

    /// get config entry nae
    const std::string& getName() const;

    /// set value from string, will be converted to the correct type
    virtual bool setFromString(const std::string& value)=0;

    /// get the value as a string
    virtual std::string getAsString() const=0;

protected:
    Type m_type;        /// stores the template type of the underlying instance
    std::string m_name; /// config entry name

public:
    /// config entry available types
    enum class Type : uint8_t
    {
        BOOL,
        INT,
        STRING,
        VEC2I,
        NONE
    };
};
////////////////////////////////////////////////////////////////////////////////
/// templated config entry
template <typename T>
class TConfigEntry : public ConfigEntry
{
public:
    TConfigEntry(const std::string& name, const T& data = T());
    virtual ~TConfigEntry() override;

    bool set(const T& data);

    virtual bool setFromString(const std::string& value) override;

    T get() const;
    virtual std::string getAsString() const override;

private:
    T m_data;
};
////////////////////////////////////////////////////////////////////////////////
/// Config class holding all the config entries
class ENGINE_EXPORT Config
{
public:
    Config();

    ~Config();

    void initDefaultConfig();
    void checkConfig();

    /// get
    const ConfigEntry* getEntry(const std::string& paramName) const;
    ConfigEntry* getEntry(const std::string& paramName);

    /// get value of paramName entry, underlying type must match
    template <typename T>
    T get(const std::string& paramName) const;

    /// set value of paramName entry, underlying type must match
    template <typename T>
    bool set(const std::string& paramName, const T& value);

    /// set value of paramName without knowing the underlying type, value string will be converted to the correct type
    bool setFromString(const std::string& paramName, const std::string& value);

    friend Logger ENGINE_EXPORT & operator<<(Logger& o, const Config& config);

public:
    TConfigEntry<std::string>* app;
    TConfigEntry<std::string>* renderplugin;
    TConfigEntry<std::string>* inputplugin;
    TConfigEntry<std::string>* audioplugin;
    TConfigEntry<std::string>* windowplugin;
    TConfigEntry<std::string>* codecplugins;
    TConfigEntry<Vec2i>* resolution;
    TConfigEntry<Vec2i>* position;
    TConfigEntry<bool>* fullscreen;
    TConfigEntry<bool>* borderless;

private:
    std::map<std::string, ConfigEntry*> m_config;   ///< mapping name <-> config entries
};
////////////////////////////////////////////////////////////////////////////////
/// Global config access
void setGlobalConfig(Config& config);
Config ENGINE_EXPORT& config();
////////////////////////////////////////////////////////////////////////////////
#endif // __CONFIG_HPP__
