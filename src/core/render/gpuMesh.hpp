#ifndef __GPUMESH_HPP__
#define __GPUMESH_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include "bufferObject.hpp"
#include "vao.hpp"
#include "shaderProgram.hpp"
////////////////////////////////////////////////////////////////////////////////
class GPUMesh;
using GPUMeshPtr = std::shared_ptr<GPUMesh>;
////////////////////////////////////////////////////////////////////////////////
class GPUMesh : public Resource
{
public:
    GPUMesh(const std::string& name);
    virtual ~GPUMesh() override;

    static GPUMeshPtr create(const std::string& name);

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
#endif // __GPUMESH_HPP__
