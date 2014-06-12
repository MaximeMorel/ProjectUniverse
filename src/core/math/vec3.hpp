#ifndef __VEC3_HPP__
#define __VEC3_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T> class TVec3;
////////////////////////////////////////////////////////////////////////////////
template <typename T> std::ostream& operator<<(std::ostream& o, const TVec3<T>& v);
template <typename T> Logger& operator<<(Logger& o, const TVec3<T>& v);
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TVec3
{
public:
    TVec3();
    TVec3(const T& x, const T& y, const T& z);

    T operator[](size_t i) const;
    T& operator[](size_t i);

    T dot(const TVec3<T>& v) const;
    TVec3<T> cross(const TVec3<T>& v) const;

    T length() const;
    T sqrLength() const;

    TVec3<T> normalize() const;

    TVec3<T> operator+(const TVec3& v) const;
    TVec3<T> operator-(const TVec3& v) const;

    TVec3<T> operator*(T f) const;
    TVec3<T> operator/(T f) const;

    TVec3<T> operator-() const;

    size_t getMemSize() const;

    friend std::ostream& operator<< <> (std::ostream& o, const TVec3<T>& v);
    friend Logger& operator<< <> (Logger& o, const TVec3<T>& v);

    T x, y, z;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T> bool operator==(const TVec3<T>& lhs, const TVec3<T>& rhs);
template <typename T> bool operator!=(const TVec3<T>& lhs, const TVec3<T>& rhs);
////////////////////////////////////////////////////////////////////////////////
typedef TVec3<int> Vec3i;
typedef TVec3<float> Vec3f;
typedef TVec3<double> Vec3d;
////////////////////////////////////////////////////////////////////////////////
typedef Vec3d Vec3;
////////////////////////////////////////////////////////////////////////////////
#include "vec3.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __VEC3_HPP__
