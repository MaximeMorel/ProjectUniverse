#ifndef __FBO_OPENGL4_HPP__
#define __FBO_OPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/fbo.hpp"
////////////////////////////////////////////////////////////////////////////////
class FBOGL4 : public FBO
{
public:
    FBOGL4(const std::string& name);
    virtual ~FBOGL4() override;

private:
    unsigned int m_fboId;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __FBO_OPENGL4_HPP__
