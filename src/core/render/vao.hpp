#ifndef __VAO_HPP__
#define __VAO_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
////////////////////////////////////////////////////////////////////////////////
class VAO;
using VAOPtr = std::shared_ptr<VAO>;
////////////////////////////////////////////////////////////////////////////////
class VAO : public Resource
{
public:
    VAO(const std::string& name);
    virtual ~VAO() override;

     uint32_t getVaoId() const;

    virtual void bind();

protected:
    virtual void printOn(Logger& o) const override;

protected:
    uint32_t m_vaoId;

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __VAO_HPP__
