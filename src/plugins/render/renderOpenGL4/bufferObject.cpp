////////////////////////////////////////////////////////////////////////////////
#include "bufferObject.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
BufferObjectGL4::BufferObjectGL4(const std::string& name)
: BufferObject(name)
{
    glGenBuffers(1, &m_bufferId);
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectGL4::~BufferObjectGL4()
{
    glDeleteBuffers(1, &m_bufferId);

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
BufferObjectPtr BufferObjectGL4::create(const std::string& name)
{
    return std::make_shared<BufferObjectGL4>(name);
}
////////////////////////////////////////////////////////////////////////////////
void BufferObjectGL4::bindVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    m_targetType = GL_ARRAY_BUFFER;
}
////////////////////////////////////////////////////////////////////////////////
void BufferObjectGL4::bindIBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
    m_targetType = GL_ELEMENT_ARRAY_BUFFER;
}
////////////////////////////////////////////////////////////////////////////////
void BufferObjectGL4::setData(const void* data, size_t size)
{
    //glNamedBufferData(m_bufferId, size, data, GL_STATIC_DRAW);
    glBufferData(m_targetType, size, data, GL_STATIC_DRAW);
}
////////////////////////////////////////////////////////////////////////////////
