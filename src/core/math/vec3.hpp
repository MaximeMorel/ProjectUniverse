#ifndef __VEC3_HPP__
#define __VEC3_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TVec3
{
public:
    /// Construct a null vector
    TVec3();

    /// Contruct by giving 3 scalars
    TVec3(const T& x, const T& y, const T& z);

    /// Construct a diagonal matrix with value v
    TVec3(const T& v);

    /// Construct by giving a pointer to an array of scalar
    explicit TVec3(const T* v);

    T operator[](size_t i) const;
    T& operator[](size_t i);

    T dot(const TVec3<T>& v) const;
    TVec3<T> cross(const TVec3<T>& v) const;

    T length() const;
    T lengthSqr() const;

    TVec3<T> normalize() const;

    TVec3<T> operator+(const TVec3& v) const;
    TVec3<T> operator-(const TVec3& v) const;

    TVec3<T> operator*(T f) const;
    TVec3<T> operator/(T f) const;

    TVec3<T> operator-() const;

    size_t getMemSize() const;

    T x, y, z;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T> Logger& operator<<(Logger& o, const TVec3<T>& v);
////////////////////////////////////////////////////////////////////////////////
template <typename T> bool operator==(const TVec3<T>& lhs, const TVec3<T>& rhs);
template <typename T> bool operator!=(const TVec3<T>& lhs, const TVec3<T>& rhs);
////////////////////////////////////////////////////////////////////////////////
using Vec3i8  = TVec3<int8_t>;
using Vec3ui8 = TVec3<uint8_t>;
using Vec3i   = TVec3<int32_t>;
using Vec3ui  = TVec3<uint32_t>;
using Vec3f   = TVec3<float>;
using Vec3d   = TVec3<double>;
////////////////////////////////////////////////////////////////////////////////
using Vec3 = Vec3d;
////////////////////////////////////////////////////////////////////////////////
#endif // __VEC3_HPP__
