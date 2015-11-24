#ifndef __RESOURCEMANAGER_HPP__
#define __RESOURCEMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "resource.hpp"
#include <string>
#include <vector>
//#include <map>
#include <unordered_map>
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    template<class T, typename... Params>
    ResourcePtr createResource(Params... p);

    void addResource(const ResourcePtr& res);

    // get by resource Id, global
    ResourcePtr getResource(int resId);

    // get by resource Id and resource type Id
    ResourcePtr getResource(int resId, int resTypeId);

    // get by resource name
    ResourcePtr getResource(const std::string& name);

    // get by resource name and resource type Id
    ResourcePtr getResource(const std::string& name, int resTypeId);

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const ResourceManager& res);

private:
    struct ResNameId
    {
        std::string name;
        int id;
    };

    // use unordered_map ?
    //std::vector<std::map<ResNameId, Resource*>> m_resources;
    //std::vector<std::map<std::string, ResourcePtr>> m_resources;
    std::vector<std::unordered_map<std::string, ResourcePtr>> m_resources;

    // registered path list

    // tool to get full path for a resource
};
////////////////////////////////////////////////////////////////////////////////
#include "resourceManager.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCEMANAGER_HPP__
