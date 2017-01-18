////////////////////////////////////////////////////////////////////////////////
#include "bufferObjectGL.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
BufferObjectGL::BufferObjectGL(const std::string& name)
: BufferObject(name)
{
    glGenBuffers(1, &m_bufferId);
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectGL::~BufferObjectGL()
{
    glDeleteBuffers(1, &m_bufferId);

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectPtr BufferObjectGL::create(const std::string& name)
{
    return std::make_shared<BufferObjectGL>(name);
}
////////////////////////////////////////////////////////////////////////////////
void BufferObjectGL::bindVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    m_targetType = GL_ARRAY_BUFFER;
}
////////////////////////////////////////////////////////////////////////////////
void BufferObjectGL::bindIBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
    m_targetType = GL_ELEMENT_ARRAY_BUFFER;
}
////////////////////////////////////////////////////////////////////////////////
void BufferObjectGL::setData(const void* data, size_t size)
{
    if (glNamedBufferData)
        glNamedBufferData(m_bufferId, size, data, GL_STATIC_DRAW);
    else
        glBufferData(m_targetType, size, data, GL_STATIC_DRAW);
}
////////////////////////////////////////////////////////////////////////////////
