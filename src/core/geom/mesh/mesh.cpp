////////////////////////////////////////////////////////////////////////////////
#include "mesh.hpp"
#include "core/engine.hpp"
#include "core/resource/resourceManager.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Mesh::type("Mesh");
////////////////////////////////////////////////////////////////////////////////
Mesh::Mesh(const std::string& name, const std::string& fileName)
    : ResourceFile(name, fileName)
{
    //m_gpuMesh = res().create<GPUMesh>(name);
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
    for (auto* codec : getEngine().codecs().getMeshCodecs())
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
    for (auto* codec : getEngine().codecs().getMeshCodecs())
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

}
////////////////////////////////////////////////////////////////////////////////
