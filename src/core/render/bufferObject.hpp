#ifndef __BUFFEROBJECT_HPP__
#define __BUFFEROBJECT_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
class BufferObject;
using BufferObjectPtr = std::shared_ptr<BufferObject>;
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT BufferObject : public Resource
{
public:
    BufferObject(const std::string& name);
    virtual ~BufferObject() override;

    static BufferObjectPtr create(const std::string& name);

    uint32_t getBufferObjectId() const;

    virtual void bindVBO();
    virtual void bindIBO();

    virtual void setData(const void* data, size_t size);

protected:
    uint32_t m_bufferId;

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __BUFFEROBJECT_HPP__
