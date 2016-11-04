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
Type getType<bool>()
{
    return Type::BOOL;
}

template <>
Type getType<int>()
{
    return Type::INT;
}

class ConfigEntry
{
public:
    Type getType() const
    {
        return m_type;
    }

    const std::string& getName() const
    {
        return m_name;
    }

protected:
    ConfigEntry(const std::string& name, Type t)
    : m_type(t)
    , m_name(name)
    {}

    Type m_type;
    std::string m_name;
};

template <typename T>
class TConfigEntry : public ConfigEntry
{
public:
    TConfigEntry(const std::string& name, const T& data = T())
        : ConfigEntry(name, Type::INT)
        , m_data(data)
    {}

    void set(const T& data)
    {
        m_data = data;
    }

    T get() const
    {
        return m_data;
    }

private:
    T m_data;
};

////////////////////////////////////////////////////////////////////////////////
class Config
{
public:
    Config()
        : app(nullptr)
        , resolution(nullptr)
    {
        ConfigEntry* c1 = new TConfigEntry<bool>("b1", true);
        m_config[c1->getName()] = c1;

        ConfigEntry* c = getC("c1");
        //c->
        std::string str("a");
        bool a = get<bool>(str);

        resolution = new TConfigEntry<std::string>("resolution", "1920x1080");
        m_config["resolution"] = resolution;
    }

    ~Config()
    {

    }

    void initDefaultConfig()
    {
        if (!resolution)
            resolution = new TConfigEntry<std::string>("resolution", "1920x1080");
        m_config["resolution"] = resolution;
    }

    const ConfigEntry* getC(const std::string& name) const
    {
        auto it = m_config.find(name);
        if (it != m_config.end())
        {
            return it->second;
        }
        return nullptr;
    }

    ConfigEntry* getC(const std::string& name)
    {
        return const_cast<ConfigEntry*>(static_cast<const Config &>(*this).getC(name));
    }

    template <typename T>
    T get(const std::string& name) const
    {
        const ConfigEntry* c = getC(name);
        if (c && c->getType() == getType<T>())
        {
            return (static_cast<const TConfigEntry<T>*>(c))->get();
        }
    }

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
