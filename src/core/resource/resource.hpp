#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/log/logger.hpp"
#include "core/engine_export.h"
#include <string>
#include <memory>
#include <ostream>
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT ResourceType
{
public:
    ResourceType(const std::string& typeName);
    uint32_t getTypeId() const;
    const std::string& getTypeName() const;

private:
    uint32_t m_typeId;
    std::string m_typeName;

    friend class ResourceManager;
};
////////////////////////////////////////////////////////////////////////////////
class Resource;
using ResourcePtr = std::shared_ptr<Resource>;
////////////////////////////////////////////////////////////////////////////////
/// \brief Resource base class
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT Resource
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

    static const char* getSearchPath();

    /// reload filed base resource when modified on disk
    virtual bool reload();

    static const ResourceType& getStaticType();
    virtual const ResourceType& getType() const;

    virtual size_t getMemSize() const;

    friend Logger ENGINE_EXPORT & operator<<(Logger& o, const Resource& res);
    friend Logger ENGINE_EXPORT & operator<<(Logger& o, ResourcePtr res);

protected:
    virtual void printOn(Logger& o) const;

    bool isEnginemanaged() const;
    bool isFile() const;

    enum Flags
    {
        ENGINE_MANAGED = 0x00000001,
        IS_FILE        = 0x00000002
    };

private:
    size_t m_id;                ///< resource id
    std::string m_name;         ///< resource name
    //uint32_t m_flags;           ///< resource flags
    //bool m_isEngineManaged;     ///< flag indicating if the resource is managed by engine (allocation / deletion)

protected:
    uint32_t m_flags;           ///< resource flags
    //bool m_isFile;              ///< true if resource is a file

private:
    friend class ResourceManager;

public:
    virtual ResourceType& dyntype() { return type; }
    virtual const ResourceType& dyntype() const { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCE_HPP__
