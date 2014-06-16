#ifndef __RESOURCEMANAGER_HPP__
#define __RESOURCEMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "resource.hpp"
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    void addResource(Resource* res);

    // get by resource Id, global
    Resource* getResource(int resId) const;

    // get by resource Id and resource type Id
    Resource* getResource(int resId, int resTypeId) const;

    // get by resource name
    Resource* getResource(const std::string& name) const;

    // get by resource name and resource type Id
    Resource* getResource(const std::string& name, int resTypeId) const;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const ResourceManager& res);

private:
    struct ResNameId
    {
        std::string name;
        int id;
    };

    std::vector<std::map<ResNameId, Resource*>> m_resources;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCEMANAGER_HPP__
