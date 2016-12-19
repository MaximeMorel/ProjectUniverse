#ifndef __MESH_HPP__
#define __MESH_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
#include "core/math/vec3.hpp"
#include "core/log/logger.hpp"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;
////////////////////////////////////////////////////////////////////////////////
class Mesh : public ResourceFile
{
public:
    Mesh(const std::string& name, const std::string& fileName);
    virtual ~Mesh() override;

    static MeshPtr create(const std::string& name, const std::string& fileName);

    virtual size_t getMemSize() const override;

    std::vector<float> m_vertices;

private:

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __MESH_HPP__
