////////////////////////////////////////////////////////////////////////////////
#include "resourceManager.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceManager::ResourceManager()
{

}
////////////////////////////////////////////////////////////////////////////////
ResourceManager::~ResourceManager()
{

}
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::addResource(const ResourcePtr& res)
{
    //ResNameId key = {res->getName(), res->getId()};
    m_resources[0][res->getName()] = res;
}
////////////////////////////////////////////////////////////////////////////////
ResourcePtr ResourceManager::getResource(int resId)
{

}
////////////////////////////////////////////////////////////////////////////////
ResourcePtr ResourceManager::getResource(int resId, int resTypeId)
{

}
////////////////////////////////////////////////////////////////////////////////
ResourcePtr ResourceManager::getResource(const std::string& name)
{
    for(std::unordered_map<std::string, ResourcePtr>& map : m_resources)
    {
        std::unordered_map<std::string, ResourcePtr>::iterator it = map.find(name);
        if(it != map.end())
        {
            return it->second;
        }
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
ResourcePtr ResourceManager::getResource(const std::string& name, int resTypeId)
{
    //return m_resources[resTypeId][name];
    std::unordered_map<std::string, ResourcePtr>& map = m_resources[resTypeId];
    std::unordered_map<std::string, ResourcePtr>::iterator it = map.find(name);
    if(it != map.end())
    {
        return it->second;
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
size_t ResourceManager::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
