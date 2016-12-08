////////////////////////////////////////////////////////////////////////////////
#include "fbo.hpp"
////////////////////////////////////////////////////////////////////////////////
FBO::FBO(const std::string& name)
: Resource(name)
{
}
////////////////////////////////////////////////////////////////////////////////
FBO::~FBO()
{
}
////////////////////////////////////////////////////////////////////////////////
uint32_t FBO::getFboId() const
{
    return m_fboId;
}
////////////////////////////////////////////////////////////////////////////////
