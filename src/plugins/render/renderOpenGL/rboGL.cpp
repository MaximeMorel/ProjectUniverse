////////////////////////////////////////////////////////////////////////////////
#include "rboGL.hpp"
////////////////////////////////////////////////////////////////////////////////
RBOGL::RBOGL()
{
    glGenRenderbuffers(1, &m_rboId);
}
////////////////////////////////////////////////////////////////////////////////
RBOGL::~RBOGL()
{
    glDeleteRenderbuffers(1, &m_rboId);
}
////////////////////////////////////////////////////////////////////////////////
bool RBOGL::init()
{
    if (m_rboId == 0)
    {
        glGenRenderbuffers(1, &m_rboId);
    }

    if (m_rboId == 0)
    {
        return false;
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
GLuint RBOGL::getRboId() const
{
    return m_rboId;
}
////////////////////////////////////////////////////////////////////////////////
void RBOGL::printOn(Logger& o) const
{
    o << "RBOGL " << m_rboId;
}
////////////////////////////////////////////////////////////////////////////////
