#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <map>
////////////////////////////////////////////////////////////////////////////////
enum class Type
{
    BOOL,
    INT
};

template <typename T>
Type getType();

template <>
Type getType<bool>();

template <>
Type getType<int>();

class ConfigEntry
{
public:
    Type getType() const;

    const std::string& getName() const;

    virtual void setString(const std::string& value);
    virtual void setInt(int value);
    virtual void setBool(bool value);
    virtual void setFloat(float value);

protected:
    ConfigEntry(const std::string& name, Type t);

    Type m_type;
    std::string m_name;
};

template <typename T>
class TConfigEntry : public ConfigEntry
{
public:
    TConfigEntry(const std::string& name, const T& data = T());

    virtual void setString(const std::string& value);
    virtual void setInt(int value);
    virtual void setBool(bool value);
    virtual void setFloat(float value);
    void setT(const T& data);

    T get() const;

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

    const ConfigEntry* getC(const std::string& name) const;

    ConfigEntry* getC(const std::string& name);

    template <typename T>
    T get(const std::string& name) const;

    /*template <typename T>
    void set(const std::string& name, const T& data)
    {

    }*/

    TConfigEntry<std::string>* app;
    TConfigEntry<std::string>* resolution;
    TConfigEntry<int>* windowmode;

private:
    std::map<std::string,ConfigEntry*> m_config;
    /*std::map<std::string,bool> m_configBool;
    std::map<std::string,int> m_configInt;
    std::map<std::string,double> m_configDouble;
    std::map<std::string,std::string> m_configString;*/
};

/*template <>
const bool& Config::get<bool>(const std::string& name) const
{
    auto it = m_configBool.find(name);
    if (it != m_configBool.end())
    {
        return it->second;
    }
    return false;
}

template <>
void Config::set<bool>(const std::string& name, const bool& data)
{
    m_configBool[name] = data;
}*/

// config.set("flag", true);
// bool flag = config.get("flag");
// std::string str = config.get("str");
////////////////////////////////////////////////////////////////////////////////
#endif // __CONFIG_HPP__
