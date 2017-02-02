#ifndef __RESOURCEMANAGER_HPP__
#define __RESOURCEMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "resource.hpp"
#include "core/log/logManager.hpp"
#include "core/engine_export.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <ostream>
#include <cstdint>
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT ResourceManager
{
public:
    ResourceManager(LogManager &logManager);
    ~ResourceManager();

    ///  Main resource creation facility
    template<class T, typename... Params>
    std::shared_ptr<T> create(const std::string& name, Params... p);

    ///  Main resource creation facility
    template<class T, typename... Params>
    std::shared_ptr<T> createFromFile(const std::string& name, Params... p);

    /*template<class T, typename... Params>
    std::shared_ptr<T> create(ResourcePtr parent, const std::string& name, Params... p);*/

    void addSearchPath(const std::string& path);

    ResourcePtr addResource(ResourcePtr res);

    void delResource(size_t resId);
    void delResource(size_t resId, const std::string& name);
    void delResource(size_t resId, size_t typeId, const std::string& name);
    void delResource(const std::string& name);
    void delResource(ResourcePtr res);
    void delResource(Resource* res);

    // get by resource Id, global
    ResourcePtr getResource(size_t resId, size_t typeId);

    // get by resource Id and resource type Id
    //ResourcePtr getResource(int resId, int resTypeId);

    // get by resource name
    ResourcePtr getResource(const std::string& name, size_t typeId);

    // get by resource name and resource type Id
    //ResourcePtr getResource(const std::string& name, int resTypeId);

    size_t getMemSize() const;

    // Sum all resources memory usage
    size_t getMemSizeFull() const;

    friend Logger& operator<<(Logger& o, const ResourceManager& res);

private:
    /// Add a resource without checking if it's already managed
    void addResourceNoCheck(ResourcePtr res);

    /// Find the path prefix of a resource (allowing to know the full path)
    std::string findPathPrefix(const std::string &fileName);

private:
    struct ResNameId
    {
        int id;
        std::string name;
    };

    // use unordered_map ?
    //std::vector<std::map<ResNameId, Resource*>> m_resources;
    //std::vector<std::map<std::string, ResourcePtr>> m_resources;
    //std::vector<std::unordered_map<std::string, ResourcePtr>> m_resources;

    class ResourcePool
    {
    public:
        ResourcePool(const std::string& poolName, uint32_t id)
            : m_name(poolName)
            , m_id(id)
        {}

        friend Logger& operator<<(Logger& o, const ResourcePool& pool);

        std::string m_name;
        uint32_t m_id;
        using ResourceWPtr = std::weak_ptr<Resource>;
        std::vector<ResourceWPtr> m_resources;    ///< array of resources
        std::unordered_map<std::string, size_t> m_resourceNames;
    };
    friend Logger& operator<<(Logger& o, const ResourcePool& pool);

    std::vector<ResourcePool> m_pools;

    using ResourceWPtr = std::weak_ptr<Resource>;
    std::vector<ResourceWPtr> m_resources;    ///< array of resources
    std::unordered_map<std::string, size_t> m_resourceNames;

    std::vector<std::string> m_searchPaths;     ///< registered path list

    // tool to get full path for a resource

    LogManager& m_logManager;
};
////////////////////////////////////////////////////////////////////////////////
/// Global resource manager access
void setGlobalResourceManager(ResourceManager& res);
ResourceManager ENGINE_EXPORT & res();
////////////////////////////////////////////////////////////////////////////////
#include "resourceManager.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCEMANAGER_HPP__
