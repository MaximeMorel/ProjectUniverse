#ifndef __RENDERMESHGL4_HPP__
#define __RENDERMESHGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/renderMesh.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
class RenderMeshGL4;
using RenderMeshGL4Ptr = std::shared_ptr<RenderMeshGL4>;
////////////////////////////////////////////////////////////////////////////////
class RenderMeshGL4 : public RenderMesh
{
public:
    RenderMeshGL4(const std::string& name);
    virtual ~RenderMeshGL4() override;

    static RenderMeshPtr create(const std::string& name);

    virtual void setup(Mesh* mesh) override;
    virtual void draw() override;

    GLsizei m_count;
    GLenum m_indicesType;

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERMESHGL4_HPP__
