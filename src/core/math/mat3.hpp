#ifndef __MAT3_HPP__
#define __MAT3_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <ostream>
#include "core/math/vec3.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TMat3
{
public:
    TMat3();
    TMat3(T f);
    TMat3(const T* v);
    TMat3(T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9);

    T operator[](size_t i) const;
    T& operator[](size_t i);

    T operator()(size_t i, size_t j) const;
    T& operator()(size_t i, size_t j);

    TMat3<T> operator*(const TMat3<T>& m) const;
    TVec3<T> operator*(const TVec3<T>& v) const;
    TMat3<T> operator*(T f) const;
    TMat3<T> operator/(T f) const;

    TMat3<T> transpose() const;

    T trace() const;
    T determinant() const;
    TMat3<T> inverse() const;

    size_t getMemSize() const;

private:
    T m_data[9];
};
////////////////////////////////////////////////////////////////////////////////
template <typename T> std::ostream& operator<<(std::ostream& o, TMat3<T> const& mat);
template <typename T> Logger& operator<<(Logger& o, TMat3<T> const& mat);
////////////////////////////////////////////////////////////////////////////////
template <typename T> bool operator==(const TMat3<T>& lhs, const TMat3<T>& rhs);
template <typename T> bool operator!=(const TMat3<T>& lhs, const TMat3<T>& rhs);
////////////////////////////////////////////////////////////////////////////////
typedef TMat3<int> Mat3i;
typedef TMat3<float> Mat3f;
typedef TMat3<double> Mat3d;
////////////////////////////////////////////////////////////////////////////////
typedef Mat3d Mat3;
////////////////////////////////////////////////////////////////////////////////
#include "mat3.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __MAT3_HPP__
