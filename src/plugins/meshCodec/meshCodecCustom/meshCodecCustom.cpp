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
bool PluginMeshCodecCustom::load(Mesh* mesh)
{
    if (!mesh)
        return false;

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
            //return loadObjIndex(mesh);
            return loadObjArray(mesh);
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
        return loadStlAscii(mesh);
    }
    else
    {
        return loadStlBinary(mesh);
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::loadStlAscii(Mesh* mesh)
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
                        mesh->m_indices.push_back(i * 3 + j);

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
            mesh->m_indices.push_back(i * 3 + j);

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
bool PluginMeshCodecCustom::loadObjIndex(Mesh* mesh)
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

                // abort if ids are out of range
                if (f.vid[i] > (vertices.size() / 3) + 1 ||
                    f.tid[i] > (texcoords.size() / 2) + 1 ||
                    f.nid[i] > (normals.size() / 3) + 1)
                    return false;
            }
            faces.push_back(f);
        }
    }

    // map vid - list of nid
    std::vector<std::vector<uint32_t>> map((vertices.size() / 3) + 1);
    for (Face& f : faces)
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
    log().log() << "nb vertices: " << vertices.size() / 3 << std::endl;//*/

    // duplicate needed vertices, and populate remap array storing id of duplicated vertices
    std::vector<std::vector<uint32_t>> remap((vertices.size() / 3) + 1);
    for (uint32_t i = 1; i < map.size(); ++i)
    {
        if (map[i].size() > 1)
        {
            remap[i].push_back(i); // original position
            for (uint32_t k = 1; k < map[i].size(); ++k)
            {
                remap[i].push_back((vertices.size() / 3) + 1);
                for (uint8_t j = 0; j < 3; ++j)
                    vertices.push_back(vertices[3 * (i - 1) + j]);
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
    log().log() << std::endl;//*/

    // reorder data
    for (Face& f : faces)
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

    mesh->m_indices.reserve(faces.size() * 3);
    mesh->m_vertices.resize(vertices.size());
    std::copy(vertices.begin(), vertices.end(), mesh->m_vertices.begin());
    mesh->m_normals.resize(vertices.size());
    for (Face& f : faces)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            mesh->m_indices.push_back(f.vid[i] - 1);

            for (uint8_t k = 0; k < 3; ++k)
                mesh->m_normals[3 * (f.vid[i] - 1) + k] = normals[3 * (f.nid[i] - 1) + k];
        }
    }

    log().log() << std::endl;

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::loadObjArray(Mesh* mesh)
{
    const std::string& fileName = mesh->getFileName();
    std::ifstream file(fileName);

    std::vector<float> vertices;
    std::vector<float> texcoords;
    std::vector<float> normals;

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
            uint32_t vid = 0;
            uint32_t tid = 0;
            uint32_t nid = 0;
            for (uint8_t i = 0; i < 3; ++i)
            {
                file >> buf;
                size_t pos1 = buf.find('/');
                if (pos1 > 0 && pos1 != std::string::npos)
                {
                    mesh->m_indices.push_back(mesh->m_vertices.size() / 3);
                    vid = std::stoi(buf.substr(0, pos1));
                    for (uint8_t j = 0; j < 3; ++j)
                        mesh->m_vertices.push_back(vertices[3 * (vid - 1) + j]);
                }
                size_t pos2 = buf.find('/', pos1 + 1);
                if (pos2 - (pos1 + 1) > 0 && pos2 != std::string::npos)
                {
                    tid = std::stoi(buf.substr(pos1 + 1, pos2 - (pos1 + 1)));
                    for (uint8_t j = 0; j < 2; ++j)
                        mesh->m_texCoords.push_back(vertices[2 * (tid - 1) + j]);
                }
                if (pos2 + 1 > 0)
                {
                    nid = std::stoi(buf.substr(pos2 + 1));
                    for (uint8_t j = 0; j < 3; ++j)
                        mesh->m_normals.push_back(normals[3 * (nid - 1) + j]);
                }
            }

            // abort if ids are out of range
            if (vid > (vertices.size() / 3) + 1 ||
                tid > (texcoords.size() / 2) + 1 ||
                nid > (normals.size() / 3) + 1)
                return false;
        }
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::save(Mesh *mesh, const std::string& filePath)
{
    if (!mesh)
        return false;

    size_t pos = filePath.rfind('.');
    if (pos != std::string::npos && filePath.length() >= 5) // min 5 chars to have something like x.stl or x.obj
    {
        if (filePath.substr(pos) == ".stl")
        {
            //return saveStlAscii(mesh, filePath);
            return saveStlBinary(mesh, filePath);
        }
        else if (filePath.substr(pos) == ".obj")
        {
            return saveObj(mesh, filePath);
        }
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::saveStlAscii(Mesh* mesh, const std::string& filePath)
{
    if (!mesh)
        return false;

    std::ofstream out(filePath);
    if (!out)
    {
        log().log() << "Cannot open " << filePath << " for writing.\n";
        return false;
    }

    out.precision(6);
    out << std::fixed;

    out << "solid exported from PluginMeshCodecCustom writer " << pluginInfo.major << "." << pluginInfo.minor << "\n";

    uint32_t vid[3] = {0, 0, 0};
    for (uint32_t id = 0; id + 2 < mesh->m_indices.size(); id += 3)
    {
        for (uint8_t i = 0; i < 3; ++i)
            vid[i] = mesh->m_indices[id + i];

        out << "facet normal " << mesh->m_normals[3 * vid[0] + 0] << " " << mesh->m_normals[3 * vid[0] + 1] << " " << mesh->m_normals[3 * vid[0] + 2] << "\n";
        out << "outer loop\n";
        for (uint8_t i = 0; i < 3; ++i)
            out << "vertex " << mesh->m_vertices[3 * vid[i] + 0] << " " << mesh->m_vertices[3 * vid[i] + 1] << " " << mesh->m_vertices[3 * vid[i] + 2] << "\n";
        out << "endloop\n";
        out << "endfacet\n";
    }

    out << "endsolid exported from PluginMeshCodecCustom writer " << pluginInfo.major << "." << pluginInfo.minor << "\n";

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::saveStlBinary(Mesh* mesh, const std::string& filePath)
{
    if (!mesh)
        return false;

    std::ofstream out(filePath, std::ios::out | std::ios::binary);
    if (!out)
    {
        log().log() << "Cannot open " << filePath << " for writing.\n";
        return false;
    }

    std::string header("exported from PluginMeshCodecCustom writer");
    header += std::to_string(pluginInfo.major) + "." + std::to_string(pluginInfo.minor);
    header.resize(80, ' ');
    out.write(header.c_str(), 80);

    uint32_t numTris = mesh->m_indices.size() / 3;
    char* s = reinterpret_cast<char*>(&numTris);
    out.write(s, sizeof(numTris));

    struct StlTriangle
    {
        float n[3];
        float v[3][3];
        uint16_t attrib;
    } tri;
    tri.attrib = 0;
    s = reinterpret_cast<char*>(&tri);

    uint32_t vid[3] = {0, 0, 0};
    for (uint32_t id = 0; id + 2 < mesh->m_indices.size(); id += 3)
    {
        for (uint8_t i = 0; i < 3; ++i)
            vid[i] = mesh->m_indices[id + i];

        for (uint8_t i = 0; i < 3; ++i)
            tri.n[i] = mesh->m_normals[3 * vid[0] + i];

        for (uint8_t j = 0; j < 3; ++j)
            for (uint8_t i = 0; i < 3; ++i)
                tri.v[j][i] = mesh->m_vertices[3 * vid[j] + i];

        out.write(s, 50);
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginMeshCodecCustom::saveObj(Mesh* mesh, const std::string& filePath)
{
    if (!mesh)
        return false;

    std::ofstream out(filePath, std::ios::out);
    if (!out)
    {
        log().log() << "Cannot open " << filePath << " for writing.\n";
        return false;
    }

    out << "# exported from PluginMeshCodecCustom writer " << pluginInfo.major << "." << pluginInfo.minor << "\n";
    out << "o mesh\n";

    out.precision(6);
    out << std::fixed;

    bool hasTexCoords = mesh->m_texCoords.size() > 0;
    bool hasNormals = mesh->m_normals.size() > 0;

    for (uint32_t i = 0; i + 2 < mesh->m_vertices.size(); i += 3)
    {
        out << "v " << mesh->m_vertices[i + 0] << " " << mesh->m_vertices[i + 1] << " " << mesh->m_vertices[i + 2] << "\n";
    }

    for (uint32_t i = 0; i + 1 < mesh->m_texCoords.size(); i += 2)
    {
        out << "vt " << mesh->m_texCoords[i + 0] << " " << mesh->m_texCoords[i + 1] << "\n";
    }

    for (uint32_t i = 0; i + 2 < mesh->m_normals.size(); i += 3)
    {
        out << "vn " << mesh->m_normals[i + 0] << " " << mesh->m_normals[i + 1] << " " << mesh->m_normals[i + 2] << "\n";
    }

    uint32_t vid[3] = {0, 0, 0};
    for (uint32_t id = 0; id + 2 < mesh->m_indices.size(); id += 3)
    {
        for (uint8_t i = 0; i < 3; ++i)
            vid[i] = mesh->m_indices[id + i];

        out << "f ";
        for (uint8_t i = 0; i < 3; ++i)
        {
            out << vid[i] + 1;
            if (hasTexCoords)
                out << "/" << vid[i] + 1;
            if (hasNormals)
            {
                if (!hasTexCoords)
                    out << "/";
                out << "/" << vid[i] + 1;
            }
            if (i < 2)
                out << " ";
        }
        out << "\n";
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
