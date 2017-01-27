////////////////////////////////////////////////////////////////////////////////
#include "mesh.hpp"
#include "core/codecs/codecManager.hpp"
#include "core/resource/resourceManager.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Mesh::type("Mesh");
////////////////////////////////////////////////////////////////////////////////
Mesh::Mesh(const std::string& name, const std::string& fileName)
    : ResourceFile(name, fileName)
{
}
////////////////////////////////////////////////////////////////////////////////
Mesh::~Mesh()
{
}
////////////////////////////////////////////////////////////////////////////////
MeshPtr Mesh::create(const std::string& name, const std::string& fileName)
{
    MeshPtr mesh = std::make_shared<Mesh>(name, fileName);
    if (!mesh)
        return nullptr;

    // go through mesh codecs plugins
    for (auto* codec : codecs().getMeshCodecs())
    {
        bool success = codec->load(mesh.get());
        if (success)
            return mesh;
    }
    log().log() << "No suitable reader for " << name << "\n";
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
bool Mesh::save(const std::string& filePath)
{
    // go through mesh codecs plugins
    for (auto* codec : codecs().getMeshCodecs())
    {
        bool success = codec->save(this, filePath);
        if (success)
            return true;
    }
    log().log() << "No suitable writer for " << getName() << " -> " << filePath << "\n";
    return false;
}
////////////////////////////////////////////////////////////////////////////////
size_t Mesh::getMemSize() const
{
    return sizeof(*this) +
           m_indices.size() * sizeof(decltype(m_indices)::value_type) +
           m_vertices.size() * sizeof(decltype(m_vertices)::value_type) +
           m_texCoords.size() * sizeof(decltype(m_texCoords)::value_type) +
           m_normals.size() * sizeof(decltype(m_normals)::value_type);
}
////////////////////////////////////////////////////////////////////////////////
