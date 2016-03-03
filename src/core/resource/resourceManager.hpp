#ifndef __RESOURCEMANAGER_HPP__
#define __RESOURCEMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "resource.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <ostream>
#include <cstdint>
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
class ResourceManager
{
public:
    ResourceManager(LogManager &logManager);
    ~ResourceManager();

    template<class T, typename... Params>
    ResourcePtr createResource(const std::string& name, Params... p);

    void addResource(const ResourcePtr& res);

    void delResource(size_t resId);
    void delResource(const std::string& name);
    void delResource(ResourcePtr res);

    // get by resource Id, global
    ResourcePtr getResource(size_t resId);

    // get by resource Id and resource type Id
    //ResourcePtr getResource(int resId, int resTypeId);

    // get by resource name
    ResourcePtr getResource(const std::string& name);

    // get by resource name and resource type Id
    //ResourcePtr getResource(const std::string& name, int resTypeId);

    size_t getMemSize() const;

    // Sum all resources memory usage
    size_t getMemSizeFull() const;

    friend Logger& operator<<(Logger& o, const ResourceManager& res);

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
    std::vector<ResourcePtr> m_resources;    ///< array of resources
    std::unordered_map<std::string, size_t> m_resourceNames;

    // registered path list

    // tool to get full path for a resource

    LogManager& m_logManager;
};
////////////////////////////////////////////////////////////////////////////////
#include "resourceManager.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCEMANAGER_HPP__
