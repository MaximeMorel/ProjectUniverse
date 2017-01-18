#ifndef __RENDERMESH_OPENGL_HPP__
#define __RENDERMESH_OPENGL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/renderMesh.hpp"
#include "core/render/bufferObject.hpp"
#include "core/render/shaderProgram.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
class RenderMeshGL : public RenderMesh
{
public:
    RenderMeshGL(const std::string& name);
    virtual ~RenderMeshGL() override;

    static RenderMeshPtr create(const std::string& name);

    virtual void setup(Mesh* mesh) override;
    virtual void draw() override;

    GLsizei m_count;
    GLenum m_indicesType;

    BufferObjectPtr i;
    BufferObjectPtr v;
    BufferObjectPtr n;
    ShaderProgramPtr shaderProgram;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERMESH_OPENGL_HPP__
