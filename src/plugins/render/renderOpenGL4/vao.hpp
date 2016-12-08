#ifndef __VAO_OPENGL4_HPP__
#define __VAO_OPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/vao.hpp"
////////////////////////////////////////////////////////////////////////////////
class VAOGL4 : public VAO
{
public:
    VAOGL4(const std::string& name);
    virtual ~VAOGL4() override;

    static VAOPtr create(const std::string& name);

    virtual void bind() override;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __VAO_OPENGL4_HPP__
