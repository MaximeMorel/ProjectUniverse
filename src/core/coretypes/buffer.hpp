#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include <vector>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Buffer : public Resource
{
public:
    Buffer();
    virtual ~Buffer();

    bool resize(size_t n);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    std::vector<T> m_buf;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACE_HPP__
