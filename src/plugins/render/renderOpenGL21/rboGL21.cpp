////////////////////////////////////////////////////////////////////////////////
#include "rbo.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
RBOGL4::RBOGL4(const std::string& name)
: RBO(name)
{
    glGenRenderbuffers(1, &m_rboId);
}
////////////////////////////////////////////////////////////////////////////////
RBOGL4::~RBOGL4()
{
    glDeleteRenderbuffers(1, &m_rboId);
}
////////////////////////////////////////////////////////////////////////////////
