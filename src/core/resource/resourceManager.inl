////////////////////////////////////////////////////////////////////////////////
#include "resourceManager.hpp"
////////////////////////////////////////////////////////////////////////////////
template<class T, typename... Params>
std::shared_ptr<T> ResourceManager::create(const std::string& name, Params... p)
{
    // check what resource pool to use, depending on type T
    ResourceType type = T::type;

    if (type.getTypeId() == 0)
    {
        // assign type id, which will define resource pool to use
    }

    // is the resource already loaded?
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
std::shared_ptr<T> ResourceManager::createFromFile(const std::string& name, Params... p)
{
    // check what resource pool to use, depending on type T
    ResourceType type = T::type;

    if (type.getTypeId() == 0)
    {
        // assign type id, which will define resource pool to use
    }

    // is the resource already loaded?
    auto it = m_resourceNames.find(name);
    if (it == m_resourceNames.end())
    {
        // get resource search path
        std::string subPath = T::getSearchPath();

        // build and check file path
        std::string path = findPathPrefix(subPath + name);
        if (!path.empty())
        {
            std::shared_ptr<T> res = T::create(name, path + subPath + name, p...);
            if (res)
            {
                res->m_isEngineManaged = true;
                res->m_isFile = true;
                addResourceNoCheck(res);
                return res;
            }
        }
        return nullptr;
    }
    return std::static_pointer_cast<T>(m_resources[it->second].lock());
}
////////////////////////////////////////////////////////////////////////////////
/*template<class T, typename... Params>
std::shared_ptr<T> ResourceManager::create(ResourcePtr parent, const std::string& name, Params... p)
{
    std::shared_ptr<T> res = create<T>(name, p...);
    return res;
}*/
////////////////////////////////////////////////////////////////////////////////
