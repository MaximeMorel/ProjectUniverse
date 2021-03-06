////////////////////////////////////////////////////////////////////////////////
#include "vaoGL33.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
VAOGL33::VAOGL33()
{
}
////////////////////////////////////////////////////////////////////////////////
VAOGL33::~VAOGL33()
{
}
////////////////////////////////////////////////////////////////////////////////
void VAOGL33::printOn(Logger& o) const
{
    o << "VAOGL33 " << m_vaoId;
}
////////////////////////////////////////////////////////////////////////////////
