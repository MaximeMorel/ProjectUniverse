#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include <vector>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TBuffer : public Resource
{
public:
    TBuffer();
    virtual ~TBuffer();

    bool resize(size_t n);
    size_t size() const;

    T operator[](size_t n) const;
    T& operator[](size_t n);

    virtual size_t getMemSize() const override;

protected:
    virtual void printOn(Logger& o) const override;

private:
    std::vector<T> m_buf;

private:
    using super = Resource;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACE_HPP__
