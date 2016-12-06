////////////////////////////////////////////////////////////////////////////////
#include "resourceManager.hpp"
////////////////////////////////////////////////////////////////////////////////
template<class T, typename... Params>
ResourcePtr ResourceManager::createResource2(const std::string& name, Params... p)
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
std::shared_ptr<T> ResourceManager::create(const std::string& name, Params... p)
{
    // check what resource pool to use, depending on type T
    auto it = m_resourceNames.find(name);
    if (it == m_resourceNames.end())
    {
        std::shared_ptr<T> res = T::create(name, p...);
        res->m_isEngineManaged = true;
        addResourceNoCheck(res);
        return res;
    }
    return std::static_pointer_cast<T>(m_resources[it->second].lock());
}
////////////////////////////////////////////////////////////////////////////////
template<class T, typename... Params>
std::shared_ptr<T> ResourceManager::create(ResourcePtr parent, const std::string& name, Params... p)
{
    std::shared_ptr<T> res = create<T>(name, p...);
    return res;
}
////////////////////////////////////////////////////////////////////////////////
