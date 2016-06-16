#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <memory>
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class ResourceType
{
public:
    int getTypeId() const;
    const std::string& getTypeName();

private:
    int m_typeId;
    std::string m_typeName;
};
////////////////////////////////////////////////////////////////////////////////
class Resource;
typedef std::shared_ptr<Resource> ResourcePtr;
////////////////////////////////////////////////////////////////////////////////
/// \brief Resource base class
////////////////////////////////////////////////////////////////////////////////
class Resource
{
public:
    Resource(const std::string& name);
    virtual ~Resource();

    Resource& operator=(const Resource& res);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get resource name
    /// \return std::string containing resource name
    ////////////////////////////////////////////////////////////////////////////
    const std::string& getName() const;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get resource id
    /// \return Resource id
    ////////////////////////////////////////////////////////////////////////////
    size_t getId() const;

    static const ResourceType& getStaticType();
    virtual const ResourceType& getType() const;

    virtual size_t getMemSize() const;

    friend Logger& operator<<(Logger& o, const Resource& res);
    friend Logger& operator<<(Logger& o, const ResourcePtr& res);

protected:
    virtual void printOn(Logger& o) const = 0;

private:
    size_t m_id;
    std::string m_name;

    static ResourceType m_type;
    friend class ResourceManager;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCE_HPP__
