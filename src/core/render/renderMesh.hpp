#ifndef __RENDERMESH_HPP__
#define __RENDERMESH_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include "bufferObject.hpp"
#include "vao.hpp"
#include "shaderProgram.hpp"
////////////////////////////////////////////////////////////////////////////////
class Mesh;
class RenderMesh;
using RenderMeshPtr = std::shared_ptr<RenderMesh>;
////////////////////////////////////////////////////////////////////////////////
class RenderMesh : public Resource
{
public:
    RenderMesh(const std::string& name);
    virtual ~RenderMesh() override;

    static RenderMeshPtr create(const std::string& name);

    virtual void setup(Mesh* mesh);

    virtual void draw();

    VAOPtr vao;
    BufferObjectPtr i;
    BufferObjectPtr v;
    BufferObjectPtr n;
    ShaderProgramPtr shaderProgram;

protected:
    virtual void printOn(Logger& o) const override;

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERMESH_HPP__
