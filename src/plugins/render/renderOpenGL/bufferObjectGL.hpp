#ifndef __BUFFEROBJECT_OPENGL_HPP__
#define __BUFFEROBJECT_OPENGL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/bufferObject.hpp"
#include "GL/glew.h"
////////////////////////////////////////////////////////////////////////////////
class BufferObjectGL : public BufferObject
{
public:
    BufferObjectGL(const std::string& name);
    virtual ~BufferObjectGL() override;

    static BufferObjectPtr create(const std::string& name);

    virtual void bindVBO() override;
    virtual void bindIBO() override;

    virtual void setData(const void* data, size_t size) override;

private:
    GLuint m_bufferId;
    GLenum m_targetType;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __BUFFEROBJECT_OPENGL_HPP__
