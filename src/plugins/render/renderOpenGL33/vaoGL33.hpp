#ifndef __VAO_OPENGL33_HPP__
#define __VAO_OPENGL33_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "vaoGL.hpp"
////////////////////////////////////////////////////////////////////////////////
class VAOGL33 : public VAOGL
{
public:
    VAOGL33();
    virtual ~VAOGL33() override;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __VAO_OPENGL33_HPP__
