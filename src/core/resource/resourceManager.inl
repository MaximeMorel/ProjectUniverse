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
        type.m_typeId = m_pools.size();
        m_pools.emplace_back(type.getTypeName(), type.getTypeId());
    }

    // is the resource already loaded?
    if (type.getTypeId() < m_pools.size())
    {
        ResourcePool& pool = m_pools[type.getTypeId()];
        auto it = pool.m_resourceNames.find(name)   ;
        if (it == pool.m_resourceNames.end())
        {
            std::shared_ptr<T> res = T::create(name, p...);
            if (res)
            {
                res->m_flags |= Resource::Flags::ENGINE_MANAGED;
                addResourceNoCheck(res);
                return res;
            }
            return nullptr;
        }
        return std::static_pointer_cast<T>(pool.m_resources[it->second].lock());
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
template<class T, typename... Params>
std::shared_ptr<T> ResourceManager::createFromFile(const std::string& name, Params... p)
{
    // check what resource pool to use, depending on type T
    ResourceType& type = T::type;

    if (type.getTypeId() == 0)
    {
        // assign type id, which will define resource pool to use
        type.m_typeId = m_pools.size();
        m_pools.emplace_back(type.getTypeName(), type.getTypeId());
    }

    // is the resource already loaded?
    if (type.getTypeId() < m_pools.size())
    {
        ResourcePool& pool = m_pools[type.getTypeId()];
        auto it = pool.m_resourceNames.find(name);
        if (it == pool.m_resourceNames.end())
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
                    res->m_flags |= Resource::Flags::ENGINE_MANAGED;
                    res->m_flags |= Resource::Flags::IS_FILE;
                    addResourceNoCheck(res);
                    return res;
                }
            }
            return nullptr;
        }
        return std::static_pointer_cast<T>(pool.m_resources[it->second].lock());
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
/*template<class T, typename... Params>
std::shared_ptr<T> ResourceManager::create(ResourcePtr parent, const std::string& name, Params... p)
{
    std::shared_ptr<T> res = create<T>(name, p...);
    return res;
}*/
////////////////////////////////////////////////////////////////////////////////
