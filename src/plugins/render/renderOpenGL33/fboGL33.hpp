#ifndef __FBO_OPENGL33_HPP__
#define __FBO_OPENGL33_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "fboGL.hpp"
////////////////////////////////////////////////////////////////////////////////
class FBOGL33 : public FBOGL
{
public:
    FBOGL33(const std::string &name);
    virtual ~FBOGL33() override;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __FBO_OPENGL33_HPP__
