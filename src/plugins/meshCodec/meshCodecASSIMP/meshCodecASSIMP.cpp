////////////////////////////////////////////////////////////////////////////////
#include "meshCodecASSIMP.hpp"
#include "core/geom/mesh/mesh.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "meshCodecASSIMP",
                          "meshCodecASSIMP",
                          "meshcodec",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginMeshCodecASSIMP* lib = nullptr;
////////////////////////////////////////////////////////////////////////////////
const PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Library* getLibInstance(Engine* engine)
{
    if (lib == nullptr)
    {
        lib = new PluginMeshCodecASSIMP(*engine);
        if (lib)
        {
            engine->codecs().addMeshCodec(lib);
        }
    }
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void closeLibInstance()
{
    if (lib)
    {
        lib->getEngine().codecs().removeMeshCodec(lib);
    }
    delete lib;
    lib = nullptr;
}
////////////////////////////////////////////////////////////////////////////////
PluginMeshCodecASSIMP::PluginMeshCodecASSIMP(Engine &engine)
    : MeshCodec(engine)
{
    log().log() << "PluginMeshCodecASSIMP start...\n";
}
////////////////////////////////////////////////////////////////////////////////
PluginMeshCodecASSIMP::~PluginMeshCodecASSIMP()
{
    log().log() << "PluginMeshCodecASSIMP stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecASSIMP::load(Mesh* mesh)
{
    if (!mesh)
        return false;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(mesh->getFileName(), aiProcessPreset_TargetRealtime_Fast);

    // If the import failed, report it
    if (!scene)
    {
        log().log() << importer.GetErrorString() << "\n";
        return false;
    }

    for (uint32_t i = 0; i < scene->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[i];
        for (uint32_t j = 0; j < mesh->mNumFaces; ++j)
        {
            aiFace& face = mesh->mFaces[j];
            for (uint32_t k = 0; k < face.mNumIndices; ++k)
            {
                return false;
            }
        }
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecASSIMP::save(Mesh* mesh, const std::string& filePath)
{
    if (!mesh)
        return false;

    Assimp::Exporter exporter;

    return false;
}
////////////////////////////////////////////////////////////////////////////////
