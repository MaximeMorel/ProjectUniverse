////////////////////////////////////////////////////////////////////////////////
#include "renderMeshGL.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/geom/mesh/mesh.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
RenderMeshGL::RenderMeshGL(const std::string& name)
    : RenderMesh(name)
    , m_count(0)
    , m_indicesType(GL_UNSIGNED_INT)
{
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshGL::~RenderMeshGL()
{
    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshPtr RenderMeshGL::create(const std::string& name)
{
    return std::make_shared<RenderMeshGL>(name);
}
////////////////////////////////////////////////////////////////////////////////
void RenderMeshGL::setup(Mesh *mesh)
{
    m_count = mesh->m_indices.size();
    i = res().create<BufferObject>(getName() + "/i");
    i->bindIBO();
    if (mesh->m_indices.size() < 255)
    {
        m_indicesType = GL_UNSIGNED_BYTE;
        std::vector<uint8_t> indices(mesh->m_indices.size());
        std::copy(mesh->m_indices.begin(), mesh->m_indices.end(), indices.begin());
        i->setData(&indices.front(), indices.size() * sizeof(uint8_t));
    }
    else if (mesh->m_indices.size() < 65535)
    {
        m_indicesType = GL_UNSIGNED_SHORT;
        std::vector<uint16_t> indices(mesh->m_indices.size());
        std::copy(mesh->m_indices.begin(), mesh->m_indices.end(), indices.begin());
        i->setData(&indices.front(), indices.size() * sizeof(uint16_t));
    }
    else
    {
        m_indicesType = GL_UNSIGNED_INT;
        i->setData(&mesh->m_indices.front(), mesh->m_indices.size() * sizeof(uint32_t));
    }

    v = res().create<BufferObject>(getName() + "/v");
    v->bindVBO();
    v->setData(&mesh->m_vertices.front(), mesh->m_vertices.size() * sizeof(float));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    n = res().create<BufferObject>(getName() + "/n");
    n->bindVBO();
    if (0 && GLEW_ARB_vertex_type_2_10_10_10_rev) // GL_INT_2_10_10_10_REV test
    {
        std::vector<GLint> normals;
        normals.reserve(mesh->m_normals.size() / 3);
        GLint v = 0;
        for (size_t i = 0; i + 2 < mesh->m_normals.size(); i += 3)
        {
            v  = (static_cast<GLint>(mesh->m_normals[i + 0] * 511.0f) & 1023) << 0;
            v += (static_cast<GLint>(mesh->m_normals[i + 1] * 511.0f) & 1023) << 10;
            v += (static_cast<GLint>(mesh->m_normals[i + 2] * 511.0f) & 1023) << 20;
            //v += (static_cast<GLint>(1.0f * 1.0f) & 3) << 30;
            //normals[i/3] = v;
            normals.push_back(v);
        }
        n->setData(&normals.front(), normals.size() * sizeof(GLint));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_INT_2_10_10_10_REV, GL_FALSE, 0, 0);
    }
    else
    {
        n->setData(&mesh->m_normals.front(), mesh->m_normals.size() * sizeof(float));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    t = res().create<BufferObject>(getName() + "/t");
    t->bindVBO();
    t->setData(&mesh->m_texCoords.front(), mesh->m_texCoords.size() * sizeof(float));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
}
////////////////////////////////////////////////////////////////////////////////
void RenderMeshGL::draw()
{
    //glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glDrawElements(GL_TRIANGLES, m_count, m_indicesType, nullptr);
}
////////////////////////////////////////////////////////////////////////////////
void RenderMeshGL::printOn(Logger& o) const
{
    o << "RenderMeshGL " << getName();
}
////////////////////////////////////////////////////////////////////////////////
