////////////////////////////////////////////////////////////////////////////////
#include "fboGL45.hpp"
////////////////////////////////////////////////////////////////////////////////
FBOGL45::FBOGL45(const std::string &name)
    : FBOGL(name)
{
}
////////////////////////////////////////////////////////////////////////////////
FBOGL45::~FBOGL45()
{
}
////////////////////////////////////////////////////////////////////////////////
void FBOGL45::printOn(Logger& o) const
{
    o << "FBOGL45 " << m_fboId;
}
////////////////////////////////////////////////////////////////////////////////
