#ifndef __VEC2_HPP__
#define __VEC2_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TVec2
{
public:
    TVec2();
    TVec2(const T& x, const T& y);

    T operator[](size_t i) const;
    T& operator[](size_t i);

    size_t getMemSize() const;

    T x, y;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T> Logger& operator<<(Logger& o, const TVec2<T>& v);
////////////////////////////////////////////////////////////////////////////////
template <typename T> bool operator==(const TVec2<T>& lhs, const TVec2<T>& rhs);
template <typename T> bool operator!=(const TVec2<T>& lhs, const TVec2<T>& rhs);
////////////////////////////////////////////////////////////////////////////////
using Vec2i = TVec2<int32_t>;
using Vec2ui = TVec2<uint32_t>;
using Vec2f = TVec2<float>;
using Vec2d = TVec2<double>;
////////////////////////////////////////////////////////////////////////////////
using Vec2 = Vec2d;
////////////////////////////////////////////////////////////////////////////////
#endif // __VEC2_HPP__
