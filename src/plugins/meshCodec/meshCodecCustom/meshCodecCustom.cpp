////////////////////////////////////////////////////////////////////////////////
#include "meshCodecCustom.hpp"
#include "core/geom/mesh/mesh.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
#include <algorithm>
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

    std::string line;
    std::getline(file, line);

    std::string buf;
    std::string buf2;

    struct StlTriangle
    {
        float n[3];
        float v[3][3];
    } tri;

    uint32_t i = 0;
    bool stop = false;
    while (file && !stop)
    {
        stop = true;
        file >> buf;
        file >> buf2;
        if (buf == "facet" && buf2 == "normal")
        {
            for (uint8_t j = 0; j < 3; ++j)
                file >> tri.n[j];

            file >> buf;
            file >> buf2;
            if (buf == "outer" && buf2 == "loop")
            {
                for (uint8_t k = 0; k < 3; ++k)
                {
                    file >> buf;
                    if (buf == "vertex")
                    {
                        for (uint8_t j = 0; j < 3; ++j)
                            file >> tri.v[k][j];
                    }
                }
                file >> buf;
                file >> buf2;
                if (buf == "endloop" && buf2 == "endfacet")
                {
                    for (uint8_t j = 0; j < 3; ++j)
                        mesh->m_indices32.push_back(i * 3 + j);

                    for (uint8_t k = 0; k < 3; ++k)
                        for (uint8_t j = 0; j < 3; ++j)
                            mesh->m_normals.push_back(tri.n[j]);

                    for (uint8_t k = 0; k < 3; ++k)
                        for (uint8_t j = 0; j < 3; ++j)
                            mesh->m_vertices.push_back(tri.v[k][j]);

                    stop = false;
                    ++i;
                }
            }
        }
        else if (buf == "endsolid")
        {
            stop = true;
        }
    }

    return true;
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
        float v[3][3];
        uint16_t attrib;
    } tri;
    s = reinterpret_cast<char*>(&tri);

    for (uint32_t i = 0; i < numTris; ++i)
    {
        file.read(s, 50);
        if (!file)
            break;

        for (uint8_t j = 0; j < 3; ++j)
            mesh->m_indices32.push_back(i * 3 + j);

        for (uint8_t k = 0; k < 3; ++k)
            for (uint8_t j = 0; j < 3; ++j)
                mesh->m_normals.push_back(tri.n[j]);

        for (uint8_t k = 0; k < 3; ++k)
            for (uint8_t j = 0; j < 3; ++j)
                mesh->m_vertices.push_back(tri.v[k][j]);
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::loadObj(Mesh* mesh)
{
    const std::string& fileName = mesh->getFileName();
    std::ifstream file(fileName);

    std::vector<float> vertices;
    std::vector<float> texcoords;
    std::vector<float> normals;

    struct Face
    {
        Face()
            : vid{0, 0, 0}
            , tid{0, 0, 0}
            , nid{0, 0, 0}
        {}
        uint32_t vid[3];
        uint32_t tid[3];
        uint32_t nid[3];
    };

    std::vector<Face> faces;

    float v[3];
    std::string buf;
    while (file >> buf)
    {
        if (buf == "v")
        {
            for (uint8_t i = 0; i < 3; ++i)
            {
                file >> v[i];
                vertices.push_back(v[i]);
            }
        }
        else if (buf == "vt")
        {
            for (uint8_t i = 0; i < 2; ++i)
            {
                file >> v[i];
                texcoords.push_back(v[i]);
            }
        }
        else if (buf == "vn")
        {
            for (uint8_t i = 0; i < 3; ++i)
            {
                file >> v[i];
                normals.push_back(v[i]);
            }
        }
        else if (buf == "f")
        {
            Face f;
            for (uint8_t i = 0; i < 3; ++i)
            {
                file >> buf;
                size_t pos1 = buf.find('/');
                if (pos1 > 0 && pos1 != std::string::npos)
                {
                    f.vid[i] = std::stoi(buf.substr(0, pos1));
                }
                size_t pos2 = buf.find('/', pos1 + 1);
                if (pos2 - (pos1 + 1) > 0 && pos2 != std::string::npos)
                {
                    f.tid[i] = std::stoi(buf.substr(pos1 + 1, pos2 - (pos1 + 1)));
                }
                if (pos2 + 1 > 0)
                {
                    f.nid[i] = std::stoi(buf.substr(pos2 + 1));
                }
            }
            faces.push_back(f);
        }
    }

    // map vid - list of nid
    std::vector<std::vector<uint32_t>> map((vertices.size() + 3) / 3);
    for (Face f : faces)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            auto it = std::find(map[f.vid[i]].begin(), map[f.vid[i]].end(), f.nid[i]);
            if (it == map[f.vid[i]].end())
            {
                map[f.vid[i]].push_back(f.nid[i]);
            }
            //log().log() << f.vid[i] << "/" << f.tid[i] << "/" << f.nid[i] << " ";
        }
        //log().log() << std::endl;
    }

    /*log().log() << std::endl;
    for (uint32_t i = 1; i < map.size(); ++i)
    {
        log().log() << i << " : ";
        for (auto m : map[i])
            log().log() << m << ", ";
        log().log() << "\n";
    }
    log().log() << "nb vertices: " << vertices.size() / 3 << std::endl;*/

    // duplicate needed vertices, and populate remap array storing id of duplicated vertices
    std::vector<std::vector<uint32_t>> remap((vertices.size() + 3) / 3);
    for (uint32_t i = 1; i < map.size(); ++i)
    {
        if (map[i].size() > 1)
        {
            remap[i].push_back(i); // original position
            for (uint32_t k = 1; k < map[i].size(); ++k)
            {
                remap[i].push_back((vertices.size() / 3) + 1);
                for (uint8_t j = 0; j < 3; ++j)
                    vertices.push_back(vertices[3 * (map[i][k] - 1) + j]);
            }
        }
    }
    /*log().log() << "nb vertices: " << vertices.size() / 3 << std::endl;
    for (uint32_t i = 1; i < remap.size(); ++i)
    {
        log().log() << i << " : ";
        for (auto m : remap[i])
            log().log() << m << ", ";
        log().log() << "\n";
    }
    log().log() << std::endl;*/

    // reorder data
    for (Face f : faces)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            if (map[f.vid[i]].size() > 1)
            {
                for (uint32_t j = 1; j < map[f.vid[i]].size(); ++j)
                {
                    // find remaped vertex id
                    if (map[f.vid[i]][j] == f.nid[i])
                    {
                        f.vid[i] = remap[f.vid[i]][j];
                        break;
                    }
                }
            }
            //log().log() << f.vid[i] << "/" << f.tid[i] << "/" << f.nid[i] << " ";
        }
        //log().log() << std::endl;
    }

    mesh->m_indices32.reserve(faces.size() * 3);
    mesh->m_vertices.resize(vertices.size());
    std::copy(vertices.begin(), vertices.end(), mesh->m_vertices.begin());
    mesh->m_normals.resize(vertices.size());
    for (Face f : faces)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            mesh->m_indices32.push_back(f.vid[i] - 1);

            for (uint8_t k = 0; k < 3; ++k)
                mesh->m_normals[3 * (f.vid[i] - 1) + k] = normals[3 * (f.nid[i] - 1) + k];
        }
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
