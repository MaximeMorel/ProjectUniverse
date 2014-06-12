#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Resource
{
public:
    Resource();
    virtual ~Resource();

    virtual size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const Resource& res);
    friend Logger& operator<<(Logger& o, const Resource& res);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCE_HPP__
