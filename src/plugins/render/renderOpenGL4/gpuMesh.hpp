#ifndef __GPUMESHGL4_HPP__
#define __GPUMESHGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/gpuMesh.hpp"
////////////////////////////////////////////////////////////////////////////////
class GPUMeshGL4;
using GPUMeshGL4Ptr = std::shared_ptr<GPUMeshGL4>;
////////////////////////////////////////////////////////////////////////////////
class GPUMeshGL4 : public GPUMesh
{
public:
    GPUMeshGL4(const std::string& name);
    virtual ~GPUMeshGL4() override;

    static GPUMeshPtr create(const std::string& name);

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __GPUMESHGL4_HPP__
