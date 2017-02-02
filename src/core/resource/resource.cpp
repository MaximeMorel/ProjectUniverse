////////////////////////////////////////////////////////////////////////////////
#include "resource.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Resource::type("Resource");
////////////////////////////////////////////////////////////////////////////////
ResourceType::ResourceType(const std::string& typeName)
    : m_typeId(0)
    , m_typeName(typeName)
{
}
////////////////////////////////////////////////////////////////////////////////
uint32_t ResourceType::getTypeId() const
{
    return m_typeId;
}
////////////////////////////////////////////////////////////////////////////////
const std::string& ResourceType::getTypeName() const
{
    return m_typeName;
}
////////////////////////////////////////////////////////////////////////////////
Resource::Resource(const std::string& name)
    : m_id(0)
    , m_name(name)
    , m_flags(0)
{

}
////////////////////////////////////////////////////////////////////////////////
Resource::~Resource()
{
    // remove from resource manager
    /*if (m_isEngineManaged)
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(m_id, m_name);
    }*/
}
////////////////////////////////////////////////////////////////////////////////
const std::string& Resource::getName() const
{
    return m_name;
}
////////////////////////////////////////////////////////////////////////////////
size_t Resource::getId() const
{
    return m_id;
}
////////////////////////////////////////////////////////////////////////////////
const char* Resource::getSearchPath()
{
    return "";
}
////////////////////////////////////////////////////////////////////////////////
bool Resource::reload()
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
const ResourceType& Resource::getStaticType()
{
    return type;
}
////////////////////////////////////////////////////////////////////////////////
const ResourceType& Resource::getType() const
{
    return type;
}
////////////////////////////////////////////////////////////////////////////////
size_t Resource::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
bool Resource::isEnginemanaged() const
{
    return (m_flags | Flags::ENGINE_MANAGED);
}
////////////////////////////////////////////////////////////////////////////////
bool Resource::isFile() const
{
    return (m_flags | Flags::IS_FILE);
}
////////////////////////////////////////////////////////////////////////////////
void Resource::printOn(Logger& o) const
{
    o << "Resource (" << dyntype().getTypeName() << ") " << getId() << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
Logger ENGINE_EXPORT & operator<<(Logger& o, const Resource& res)
{
    res.printOn(o);
    return o;
}
////////////////////////////////////////////////////////////////////////////////
Logger ENGINE_EXPORT & operator<<(Logger& o, ResourcePtr res)
{
    if (res)
        res->printOn(o);
    return o;
}
////////////////////////////////////////////////////////////////////////////////
