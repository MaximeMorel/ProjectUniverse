#ifndef __RENDERMESHGL45_HPP__
#define __RENDERMESHGL45_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "renderMeshGL.hpp"
#include "vaoGL.hpp"
////////////////////////////////////////////////////////////////////////////////
class RenderMeshGL45 : public RenderMeshGL
{
public:
    RenderMeshGL45(const std::string& name);
    virtual ~RenderMeshGL45() override;

    static RenderMeshPtr create(const std::string& name);

    virtual void setup(Mesh* mesh) override;
    virtual void draw() override;

    VAOGL vao;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERMESHGL45_HPP__
