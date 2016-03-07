#ifndef __BUFFEROBJECT_NULL_HPP__
#define __BUFFEROBJECT_NULL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/bufferObject.hpp"
////////////////////////////////////////////////////////////////////////////////
class BufferObjectNull : public BufferObject
{
public:
    BufferObjectNull(const std::string& name);
    virtual ~BufferObjectNull() override;

private:
    unsigned int m_bufferId;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __BUFFEROBJECT_NULL_HPP__