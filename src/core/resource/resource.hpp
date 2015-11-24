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
/// \brief Resource base class
////////////////////////////////////////////////////////////////////////////////
class Resource
{
public:
    Resource(const std::string& name);
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
    int getId() const;

    static ResourceType& getType();

    virtual size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const Resource& res);
    friend Logger& operator<<(Logger& o, const Resource& res);

protected:
    virtual void printOn(std::ostream& o) const=0;
    virtual void printOn(Logger& o) const=0;

private:
    std::string m_name;
    int m_id;

    static ResourceType m_type;
};
////////////////////////////////////////////////////////////////////////////////
typedef std::shared_ptr<Resource> ResourcePtr;
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCE_HPP__
