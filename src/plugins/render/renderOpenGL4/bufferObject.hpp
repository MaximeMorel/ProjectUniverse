#ifndef __BUFFEROBJECT_OPENGL4_HPP__
#define __BUFFEROBJECT_OPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/bufferObject.hpp"
////////////////////////////////////////////////////////////////////////////////
class BufferObjectGL4 : public BufferObject
{
public:
    BufferObjectGL4(const std::string& name);
    virtual ~BufferObjectGL4() override;

    static BufferObjectPtr create(const std::string& name);

    virtual void bindVBO() override;
    virtual void bindIBO() override;

    virtual void setData(const void* data, size_t size) override;

private:
    uint32_t m_targetType;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __BUFFEROBJECT_OPENGL4_HPP__
