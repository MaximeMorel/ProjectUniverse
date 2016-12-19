////////////////////////////////////////////////////////////////////////////////
#include "mesh.hpp"
#include "core/engine.hpp"
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
    // go through mesh codecs plugins
    for (auto* codec : getEngine().codecs().getMeshCodecs())
    {
        bool success = codec->load(mesh);
        if (success)
            return mesh;
    }
    log().log() << "No suitable reader for " << name << "\n";
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
size_t Mesh::getMemSize() const
{

}
////////////////////////////////////////////////////////////////////////////////
