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

    friend class ResourceManager;
};
////////////////////////////////////////////////////////////////////////////////
class Resource;
using ResourcePtr = std::shared_ptr<Resource>;
////////////////////////////////////////////////////////////////////////////////
/// \brief Resource base class
////////////////////////////////////////////////////////////////////////////////
class Resource
{
protected:
    Resource(const std::string& name);

public:
    virtual ~Resource();

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
    friend Logger& operator<<(Logger& o, ResourcePtr res);

protected:
    virtual void printOn(Logger& o) const;

private:
    size_t m_id;            ///< resource id
    std::string m_name;     ///< resource name
    bool m_isEngineManaged; ///< flag indicating if the resource is managed by engine (allocation / deletion)

protected:
    bool m_isFile;

private:
    static ResourceType m_type;
    friend class ResourceManager;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCE_HPP__
