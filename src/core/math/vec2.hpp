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
template <typename T> std::ostream& operator<<(std::ostream& o, const TVec2<T>& v);
template <typename T> Logger& operator<<(Logger& o, const TVec2<T>& v);
////////////////////////////////////////////////////////////////////////////////
template <typename T> bool operator==(const TVec2<T>& lhs, const TVec2<T>& rhs);
template <typename T> bool operator!=(const TVec2<T>& lhs, const TVec2<T>& rhs);
////////////////////////////////////////////////////////////////////////////////
typedef TVec2<int> Vec2i;
typedef TVec2<float> Vec2f;
typedef TVec2<double> Vec2d;
////////////////////////////////////////////////////////////////////////////////
typedef Vec2d Vec2;
////////////////////////////////////////////////////////////////////////////////
#include "vec2.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __VEC2_HPP__
