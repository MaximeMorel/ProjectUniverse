#ifndef __RENDERMESHGL33_HPP__
#define __RENDERMESHGL33_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "renderMeshGL.hpp"
#include "vaoGL.hpp"
////////////////////////////////////////////////////////////////////////////////
class RenderMeshGL33 : public RenderMeshGL
{
public:
    RenderMeshGL33(const std::string& name);
    virtual ~RenderMeshGL33() override;

    static RenderMeshPtr create(const std::string& name);

    virtual void setup(Mesh* mesh) override;
    virtual void draw() override;

    VAOGL vao;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERMESHGL33_HPP__
