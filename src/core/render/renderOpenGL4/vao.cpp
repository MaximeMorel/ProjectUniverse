////////////////////////////////////////////////////////////////////////////////
#include "vao.hpp"
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
}
////////////////////////////////////////////////////////////////////////////////
