////////////////////////////////////////////////////////////////////////////////
#include "resource.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Resource::m_type;// = {0, "Resource"};
////////////////////////////////////////////////////////////////////////////////
Resource::Resource(const std::string& name)
: m_name(name)
{

}
////////////////////////////////////////////////////////////////////////////////
Resource::~Resource()
{
}
////////////////////////////////////////////////////////////////////////////////
const std::string& Resource::getName() const
{
    return m_name;
}
////////////////////////////////////////////////////////////////////////////////
int Resource::getId() const
{
    return m_id;
}
////////////////////////////////////////////////////////////////////////////////
ResourceType& Resource::getType()
{
    return m_type;
}
////////////////////////////////////////////////////////////////////////////////
size_t Resource::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& o, const Resource& res)
{
    res.printOn(o);
    return o;
}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const Resource& res)
{
    res.printOn(o);
    return o;
}
////////////////////////////////////////////////////////////////////////////////
