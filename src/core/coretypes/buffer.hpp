#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include <vector>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Buffer;
using BufferPtr = std::shared_ptr<Buffer>;
////////////////////////////////////////////////////////////////////////////////
class Buffer : public Resource
{
public:
    Buffer();
    virtual ~Buffer();

    virtual bool resize(size_t n);
    virtual size_t size() const;
    virtual size_t elementSize() const;

private:
    using super = Resource;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TBuffer : public Buffer
{
public:
    TBuffer();
    virtual ~TBuffer() override;

    virtual bool resize(size_t n) override;
    virtual size_t size() const override;
    virtual size_t elementSize() const override;

    T operator[](size_t n) const;
    T& operator[](size_t n);

    virtual size_t getMemSize() const override;

protected:
    virtual void printOn(Logger& o) const override;

private:
    std::vector<T> m_buf;

private:
    using super = Buffer;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACE_HPP__
