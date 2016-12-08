////////////////////////////////////////////////////////////////////////////////
#include "resourceManager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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
    m_resourceNames[res->getName()] = m_resources.size();
    res->m_id = m_resources.size();
    m_resources.push_back(res);
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
    delResource(res->getId());
}
////////////////////////////////////////////////////////////////////////////////
ResourcePtr ResourceManager::getResource(size_t resId)
{
    return m_resources[resId].lock();
}
////////////////////////////////////////////////////////////////////////////////
/*ResourcePtr ResourceManager::getResource(int resId, int resTypeId)
{
    return m_resources[resId];
}*/
////////////////////////////////////////////////////////////////////////////////
ResourcePtr ResourceManager::getResource(const std::string& name)
{
    /*for (auto& map : m_resources)
    {
        auto it = map.find(name);
        if (it != map.end())
        {
            return it->second;
        }
    }*/
    auto it = m_resourceNames.find(name);
    if (it != m_resourceNames.end())
    {
        return m_resources[it->second].lock();
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
    o << "Resources map:\n";
    size_t i = 0;
    for (auto it : res.m_resources)
    {
        o << i++ << ": " << it.lock() << "\n";
    }

    o << "Resources names:\n";
    for (auto it : res.m_resourceNames)
    {
        o << it.first << " - " << it.second << "\n";
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
