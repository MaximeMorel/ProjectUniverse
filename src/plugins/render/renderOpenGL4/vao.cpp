////////////////////////////////////////////////////////////////////////////////
#include "vao.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
VAOGL4::VAOGL4(const std::string& name)
: VAO(name)
{
    glGenVertexArrays(1, &m_vaoId);
}
////////////////////////////////////////////////////////////////////////////////
VAOGL4::~VAOGL4()
{
    glDeleteVertexArrays(1, &m_vaoId);

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(getId(), getName());
    }
}
////////////////////////////////////////////////////////////////////////////////
VAOPtr VAOGL4::create(const std::string& name)
{
    return std::make_shared<VAOGL4>(name);
}
////////////////////////////////////////////////////////////////////////////////
void VAOGL4::bind()
{
    glBindVertexArray(m_vaoId);
}
////////////////////////////////////////////////////////////////////////////////
void VAOGL4::printOn(Logger& o) const
{
    o << "VAOGL4 " << m_vaoId << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
