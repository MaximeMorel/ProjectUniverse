////////////////////////////////////////////////////////////////////////////////
#include "meshCodecCustom.hpp"
#include "core/geom/mesh/mesh.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "meshCodecCustom",
                          "meshCodecCustom",
                          "meshcodec",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginMeshCodecCustom* lib = nullptr;
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
        lib = new PluginMeshCodecCustom(*engine);
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
PluginMeshCodecCustom::PluginMeshCodecCustom(Engine &engine)
    : MeshCodec(engine)
{
    log().log() << "PluginMeshCodecCustom start...\n";
}
////////////////////////////////////////////////////////////////////////////////
PluginMeshCodecCustom::~PluginMeshCodecCustom()
{
    log().log() << "PluginMeshCodecCustom stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::load(MeshPtr mesh)
{
    return load(mesh.get());
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::load(Mesh* mesh)
{
    const std::string& fileName = mesh->getFileName();
    size_t pos = fileName.rfind('.');
    if (pos != std::string::npos && fileName.length() >= 5) // min 5 chars to have something like x.stl or x.obj
    {
        if (fileName.substr(pos) == ".stl")
        {
            return loadStl(mesh);
        }
        else if (fileName.substr(pos) == ".obj")
        {
            return loadObj(mesh);
        }
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::loadStl(Mesh* mesh)
{
    const std::string& fileName = mesh->getFileName();
    std::ifstream file(fileName);
    char header[80];
    file.getline(header, sizeof(header));
    file.close();
    std::string line(header);
    size_t pos = line.find("solid ");
    if (pos == 0)
    {
        return loadStlText(mesh);
    }
    else
    {
        return loadStlBinary(mesh);
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::loadStlText(Mesh* mesh)
{
    const std::string& fileName = mesh->getFileName();
    std::ifstream file(fileName);
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::loadStlBinary(Mesh* mesh)
{
    const std::string& fileName = mesh->getFileName();
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    file.seekg(80);
    uint32_t numTris = 0;
    char* s = reinterpret_cast<char*>(&numTris);
    file.read(s, sizeof(numTris));

    struct StlTriangle
    {
        float n[3];
        float v1[3];
        float v2[3];
        float v3[3];
        uint16_t attrib;
    } tri;
    s = reinterpret_cast<char*>(&tri);

    for (uint32_t i = 0; i < numTris; ++i)
    {
        file.read(s, 50);
        if (!file)
            break;

        for (uint8_t k = 0; k < 3; ++k)
            for (uint8_t j = 0; j < 3; ++j)
                mesh->m_normals.push_back(tri.n[j]);

        for (uint8_t j = 0; j < 3; ++j)
            mesh->m_vertices.push_back(tri.v1[j]);
        for (uint8_t j = 0; j < 3; ++j)
            mesh->m_vertices.push_back(tri.v2[j]);
        for (uint8_t j = 0; j < 3; ++j)
            mesh->m_vertices.push_back(tri.v3[j]);
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::loadObj(Mesh* mesh)
{
    const std::string& fileName = mesh->getFileName();
    std::ifstream file(fileName);
    return false;
}
////////////////////////////////////////////////////////////////////////////////
