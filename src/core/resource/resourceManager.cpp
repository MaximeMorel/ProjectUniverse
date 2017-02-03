////////////////////////////////////////////////////////////////////////////////
#include "resourceManager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
////////////////////////////////////////////////////////////////////////////////
// ideas: store resources in array, ordered, a resource can be found by id
// when deleting a resource, maintain a list of holes
// later when reinserting a resource, use holes in this list
// maintain a map of strings / id allowing to lookup by name too
////////////////////////////////////////////////////////////////////////////////
ResourceManager* gRes = nullptr;
////////////////////////////////////////////////////////////////////////////////
ResourceManager::ResourceManager(LogManager& logManager)
    : m_logManager(logManager)
{
    addSearchPath("data/");
    addSearchPath("./");
    m_pools.emplace_back("Default", 0);
}
////////////////////////////////////////////////////////////////////////////////
ResourceManager::~ResourceManager()
{
    // clean resources allocted in plugin before plugin deallocation
    // use weak ptr ?
}
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::addSearchPath(const std::string& path)
{
    m_searchPaths.push_back(path);
}
////////////////////////////////////////////////////////////////////////////////
ResourcePtr ResourceManager::addResource(ResourcePtr res)
{
    auto it = m_resourceNames.find(res->getName());
    if (it == m_resourceNames.end())
    {
        m_resourceNames[res->getName()] = m_resources.size();
        res->m_id = m_resources.size();
        m_resources.push_back(res);
    }

    return res;
}
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::addResourceNoCheck(ResourcePtr res)
{
    // no pool
    /*m_resourceNames[res->getName()] = m_resources.size();
    res->m_id = m_resources.size();
    m_resources.push_back(res);*/

    // pool
    uint32_t typeId = res->dyntype().getTypeId();
    if (typeId < m_pools.size())
    {
        ResourcePool& pool = m_pools[typeId];
        pool.m_resourceNames[res->getName()] = pool.m_resources.size();
        res->m_id = pool.m_resources.size();
        pool.m_resources.push_back(res);
    }
}
////////////////////////////////////////////////////////////////////////////////
std::string ResourceManager::findPathPrefix(const std::string& fileName)
{
    std::string path;
    struct stat st;
    for (const auto& base : m_searchPaths)
    {
        path = base + fileName;
        int err = stat(path.c_str(), &st);
        if (err == 0)
        {
            return base;
        }
    }
    return "";
}
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::delResource(size_t resId, const std::string& name)
{
    m_logManager.log() << "Deleting resource " << resId << " - " << name << std::endl;
    if (resId < m_resources.size())
    {
        ResourcePtr res = m_resources[resId].lock();
        if (res)
        {
            m_resourceNames.erase(res->getName());

            // manage the hole in the resource array
            if (resId < m_resources.size() - 1)
            {
                // swap the last element and move it in the hole
                m_resources[resId] = m_resources.back();
                m_resources[resId].lock()->m_id = resId;
                m_resourceNames[m_resources.back().lock()->getName()] = resId;
            }
            m_resources.pop_back();
        }
        else
        {
            m_resourceNames.erase(name);

            // manage the hole in the resource array
            if (resId < m_resources.size() - 1)
            {
                // swap the last element and move it in the hole
                m_resources[resId] = m_resources.back();
                if (m_resources[resId].lock())
                {
                    m_resources[resId].lock()->m_id = resId;
                    m_resourceNames[m_resources.back().lock()->getName()] = resId;
                }
            }
            m_resources.pop_back();
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::delResource(size_t resId, size_t typeId, const std::string& name)
{
    m_logManager.log() << "Deleting resource " << resId << " - " << name << " - pool: " << typeId << std::endl;
    if (typeId < m_pools.size())
    {
        ResourcePool& pool = m_pools[typeId];
        pool.m_resourceNames.erase(name);

        // manage the hole in the resource array
        if (pool.m_resources.size() > 0)
        {
            if (resId < pool.m_resources.size() - 1)
            {
                // swap the last element and move it in the hole
                pool.m_resources[resId] = pool.m_resources.back();
                ResourcePtr res = pool.m_resources[resId].lock();
                if (res)
                {
                    res->m_id = resId;
                    pool.m_resourceNames[pool.m_resources.back().lock()->getName()] = resId;
                }
            }
            pool.m_resources.pop_back();
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::delResource(size_t resId)
{
    if (resId < m_resources.size())
    {
        ResourcePtr res = m_resources[resId].lock();
        if (res)
        {
            m_logManager.log() << "Deleting resource " << resId << " - " << res->getName() << std::endl;
            m_resourceNames.erase(res->getName());

            // manage the hole in the resource array
            if (resId < m_resources.size() - 1)
            {
                // swap the last element and move it in the hole
                m_resources[resId] = m_resources.back();
                m_resources[resId].lock()->m_id = resId;
                m_resourceNames[m_resources.back().lock()->getName()] = resId;
            }
            m_resources.pop_back();
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::delResource(const std::string& name)
{
    auto it = m_resourceNames.find(name);
    if (it != m_resourceNames.end())
    {
        delResource(it->second);
    }
}
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::delResource(ResourcePtr res)
{
    delResource(res->getId(), res->dyntype().getTypeId(), res->getName());
}
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::delResource(Resource* res)
{
    delResource(res->getId(), res->dyntype().getTypeId(), res->getName());
}
////////////////////////////////////////////////////////////////////////////////
ResourcePtr ResourceManager::getResource(size_t resId, size_t typeId)
{
    if (typeId < m_pools.size())
    {
        ResourcePool& pool = m_pools[typeId];
        if (resId < pool.m_resources.size())
        {
            return pool.m_resources[resId].lock();
        }
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
ResourcePtr ResourceManager::getResource(const std::string& name, size_t typeId)
{
    if (typeId < m_pools.size())
    {
        ResourcePool& pool = m_pools[typeId];
        auto it = pool.m_resourceNames.find(name);
        if (it != pool.m_resourceNames.end())
        {
            return pool.m_resources[it->second].lock();
        }
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
/*ResourcePtr ResourceManager::getResource(const std::string& name, int resTypeId)
{
    //return m_resources[resTypeId][name];
    std::unordered_map<std::string, ResourcePtr>& map = m_resources[resTypeId];
    std::unordered_map<std::string, ResourcePtr>::iterator it = map.find(name);
    if (it != map.end())
    {
        return it->second;
    }
    return nullptr;
}*/
////////////////////////////////////////////////////////////////////////////////
size_t ResourceManager::getMemSize() const
{
    return sizeof(*this) +
           sizeof(ResourcePtr) * m_resources.capacity() +
           sizeof(std::pair<std::string, int>) * m_resourceNames.size();
}
////////////////////////////////////////////////////////////////////////////////
size_t ResourceManager::getMemSizeFull() const
{
    size_t mem = getMemSize();
    for (auto it : m_resources)
    {
        mem += it.lock()->getMemSize();
    }
    return mem;
}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const ResourceManager& res)
{
    o << "Resource pools:\n";
    for (const auto& it : res.m_pools)
    {
        o << it;
    }

    /*o << "Resources map:\n";
    size_t i = 0;
    for (auto it : res.m_resources)
    {
        o << i++ << ": " << it.lock() << "\n";
    }

    o << "Resources names:\n";
    for (auto it : res.m_resourceNames)
    {
        o << it.first << " - " << it.second << "\n";
    }*/
    return o;
}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const ResourceManager::ResourcePool& pool)
{
    o << pool.m_id << ": " << pool.m_name;
    if (pool.m_resources.size() > 0 || pool.m_resourceNames.size() > 0)
    {
        o << "\n\tResources map:\n";
        size_t i = 0;
        for (auto it : pool.m_resources)
        {
            o << "\t" << i++ << ": " << it.lock() << "\n";
        }

        o << "\tResources names:\n";
        for (auto it : pool.m_resourceNames)
        {
            o << "\t" << it.first << " - " << it.second << "\n";
        }
    }
    else
    {
        o << " empty\n";
    }
    return o;
}
////////////////////////////////////////////////////////////////////////////////
/// Global resource manager access
void setGlobalResourceManager(ResourceManager& res)
{
    gRes = &res;
}
////////////////////////////////////////////////////////////////////////////////
ResourceManager& res()
{
    return *gRes;
}
////////////////////////////////////////////////////////////////////////////////
