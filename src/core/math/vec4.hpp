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
    TVec4();
    TVec4(const T& x, const T& y, const T& z, const T& w);
    TVec4(const TVec3<T>& v, const T& w);

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
//template <typename T> std::ostream& operator<<(std::ostream& o, const TVec4<T>& v);
template <typename T> Logger& operator<<(Logger& o, const TVec4<T>& v);
////////////////////////////////////////////////////////////////////////////////
template <typename T> bool operator==(const TVec4<T>& lhs, const TVec4<T>& rhs);
template <typename T> bool operator!=(const TVec4<T>& lhs, const TVec4<T>& rhs);
////////////////////////////////////////////////////////////////////////////////
typedef TVec4<int> Vec4i;
typedef TVec4<float> Vec4f;
typedef TVec4<double> Vec4d;
////////////////////////////////////////////////////////////////////////////////
typedef Vec4d Vec4;
////////////////////////////////////////////////////////////////////////////////
//#include "vec4.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __VEC4_HPP__
