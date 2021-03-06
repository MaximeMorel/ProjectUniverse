////////////////////////////////////////////////////////////////////////////////
#include "vao.hpp"
//#include "renderManager.hpp"
//#include "renderPlugin.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType VAO::type("VAO");
////////////////////////////////////////////////////////////////////////////////
VAO::VAO(const std::string& name)
: Resource(name)
{
}
////////////////////////////////////////////////////////////////////////////////
VAO::~VAO()
{
}
////////////////////////////////////////////////////////////////////////////////
void VAO::bind()
{
}
////////////////////////////////////////////////////////////////////////////////
uint32_t VAO::getVaoId() const
{
    return m_vaoId;
}
////////////////////////////////////////////////////////////////////////////////
void VAO::printOn(Logger& o) const
{
    o << "VAO " << m_vaoId << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
