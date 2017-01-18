#ifndef __RBO_OPENGL33_HPP__
#define __RBO_OPENGL33_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "rboGL.hpp"
////////////////////////////////////////////////////////////////////////////////
class RBOGL33 : public RBOGL
{
public:
    RBOGL33();
    virtual ~RBOGL33() override;

protected:
    void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RBO_OPENGL33_HPP__