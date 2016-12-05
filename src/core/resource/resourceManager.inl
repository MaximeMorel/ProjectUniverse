////////////////////////////////////////////////////////////////////////////////
#include "resourceManager.hpp"
////////////////////////////////////////////////////////////////////////////////
template<class T, typename... Params>
ResourcePtr ResourceManager::createResource(const std::string& name, Params... p)
{
    auto it = m_resourceNames.find(name);
    if (it == m_resourceNames.end())
    {
        ResourcePtr res = std::shared_ptr<T>(new T(name, p...));
        addResourceNoCheck(res);
        return res;
    }
    return m_resources[it->second].lock();
}
////////////////////////////////////////////////////////////////////////////////
template<class T, typename... Params>
ResourcePtr ResourceManager::createResource2(const std::string& name, Params... p)
{
    auto it = m_resourceNames.find(name);
    if (it == m_resourceNames.end())
    {
        ResourcePtr res = T::create(name, p...);
        addResourceNoCheck(res);
        return res;
    }
    return m_resources[it->second].lock();
}
////////////////////////////////////////////////////////////////////////////////
