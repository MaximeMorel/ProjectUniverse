////////////////////////////////////////////////////////////////////////////////
#include "renderMesh.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/geom/mesh/mesh.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
ResourceType RenderMeshGL4::type("RenderMeshGL4");
////////////////////////////////////////////////////////////////////////////////
RenderMeshGL4::RenderMeshGL4(const std::string& name)
: RenderMesh(name)
{
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshGL4::~RenderMeshGL4()
{
    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
RenderMeshPtr RenderMeshGL4::create(const std::string& name)
{
    return std::make_shared<RenderMeshGL4>(name);
}
////////////////////////////////////////////////////////////////////////////////
void RenderMeshGL4::setup(Mesh *mesh)
{
    vao = res().create<VAO>(getName());
    vao->bind();

    i = res().create<BufferObject>(getName() + "i");
    i->bindIBO();
    i->setData(&mesh->m_indices32.front(), mesh->m_indices32.size() * sizeof(uint32_t));

    v = res().create<BufferObject>(getName() + "v");
    v->bindVBO();
    v->setData(&mesh->m_vertices.front(), mesh->m_vertices.size() * sizeof(float));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    n = res().create<BufferObject>(getName() + "n");
    n->bindVBO();
    n->setData(&mesh->m_normals.front(), mesh->m_normals.size() * sizeof(float));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
////////////////////////////////////////////////////////////////////////////////
