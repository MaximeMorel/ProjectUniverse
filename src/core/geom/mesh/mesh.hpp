#ifndef __MESH_HPP__
#define __MESH_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
#include "core/render/renderMesh.hpp"
#include "core/math/vec3.hpp"
#include "core/log/logger.hpp"
#include "core/engine_export.h"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT Mesh : public ResourceFile
{
public:
    Mesh(const std::string& name, const std::string& fileName);
    virtual ~Mesh() override;

    static MeshPtr create(const std::string& name, const std::string& fileName);
    bool save(const std::string& filePath);

    virtual size_t getMemSize() const override;

    std::vector<uint32_t> m_indices;
    std::vector<float> m_vertices;
    std::vector<float> m_texCoords;
    std::vector<float> m_normals;
    RenderMeshPtr m_renderMesh;

private:

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __MESH_HPP__
