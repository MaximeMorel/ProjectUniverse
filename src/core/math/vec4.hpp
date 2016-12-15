#ifndef __VEC4_HPP__
#define __VEC4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "vec3.hpp"
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TVec4
{
public:
    /// Construct a null vector
    TVec4();

    /// Contruct by giving 4 scalars
    TVec4(const T& x, const T& y, const T& z, const T& w);

    /// Construct by giving a vec3 and the 4th scalar
    TVec4(const TVec3<T>& v, const T& w);

    /// Construct a diagonal matrix with value v
    TVec4(const T& v);

    /// Construct by giving a pointer to an array of scalar
    TVec4(const T* v);

    T operator[](size_t i) const;
    T& operator[](size_t i);

    T dot(const TVec4<T>& v) const;
    TVec3<T> cross(const TVec4<T>& v) const;

    T length() const;
    T lengthSqr() const;

    TVec4<T> normalize() const;

    TVec4<T> operator+(const TVec4& v) const;
    TVec4<T> operator-(const TVec4& v) const;

    TVec4<T> operator*(T f) const;
    TVec4<T> operator/(T f) const;

    TVec4<T> operator-() const;

    size_t getMemSize() const;

    T x, y, z, w;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T> Logger& operator<<(Logger& o, const TVec4<T>& v);
////////////////////////////////////////////////////////////////////////////////
template <typename T> bool operator==(const TVec4<T>& lhs, const TVec4<T>& rhs);
template <typename T> bool operator!=(const TVec4<T>& lhs, const TVec4<T>& rhs);
////////////////////////////////////////////////////////////////////////////////
using Vec4i8  = TVec4<int8_t>;
using Vec4ui8 = TVec4<uint8_t>;
using Vec4i   = TVec4<int32_t>;
using Vec4ui  = TVec4<uint32_t>;
using Vec4f   = TVec4<float>;
using Vec4d   = TVec4<double>;
////////////////////////////////////////////////////////////////////////////////
using Vec4 = Vec4d;
////////////////////////////////////////////////////////////////////////////////
#endif // __VEC4_HPP__
