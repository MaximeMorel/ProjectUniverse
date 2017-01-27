#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/log/logger.hpp"
#include "core/math/vec2.hpp"
#include <string>
#include <map>
////////////////////////////////////////////////////////////////////////////////
enum class Type : uint8_t
{
    BOOL,
    INT,
    STRING,
    VEC2I
};
////////////////////////////////////////////////////////////////////////////////
class ConfigEntry
{
protected:
    ConfigEntry(const std::string& name, Type t);

public:
    virtual ~ConfigEntry();

    Type getType() const;

    const std::string& getName() const;

    virtual void set(const std::string& value);
    virtual void setString(const std::string& value);
    virtual void setInt(int value);
    virtual void setBool(bool value);
    virtual void setFloat(float value);

    virtual std::string getAsString() const;

protected:
    Type m_type;
    std::string m_name;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TConfigEntry : public ConfigEntry
{
public:
    TConfigEntry(const std::string& name, const T& data = T());
    virtual ~TConfigEntry() override;

    virtual void set(const std::string& value) override;
    virtual void setString(const std::string& value) override;
    virtual void setInt(int value) override;
    virtual void setBool(bool value) override;
    virtual void setFloat(float value) override;
    void setT(const T& data);

    T get() const;
    virtual std::string getAsString() const override;

private:
    T m_data;
};
////////////////////////////////////////////////////////////////////////////////
class Config
{
public:
    Config();

    ~Config();

    void initDefaultConfig();
    void checkConfig();

    const ConfigEntry* getEntry(const std::string& paramName) const;

    ConfigEntry* getEntry(const std::string& paramName);

    template <typename T>
    T get(const std::string& paramName) const;

    template <typename T>
    void set(const std::string& paramName, const T& value);

    void set(const std::string& paramName, const std::string& value);

    friend Logger& operator<<(Logger& o, const Config& config);

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
    std::map<std::string, ConfigEntry*> m_config;
};
////////////////////////////////////////////////////////////////////////////////
/// Global config access
void setGlobalConfig(Config& config);
Config& config();
////////////////////////////////////////////////////////////////////////////////
#endif // __CONFIG_HPP__
