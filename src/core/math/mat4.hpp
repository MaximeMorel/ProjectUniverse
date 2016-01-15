#ifndef __MAT4_HPP__
#define __MAT4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "vec3.hpp"
#include "vec4.hpp"
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TMat4
{
public:
    TMat4();
    TMat4(T f);
    TMat4(const T* v);
    TMat4(T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9, T v10, T v11, T v12, T v13, T v14, T v15, T v16);

    T operator[](size_t i) const;
    T& operator[](size_t i);

    T operator()(size_t i, size_t j) const;
    T& operator()(size_t i, size_t j);

    TMat4<T> operator*(const TMat4<T>& m) const;
    TVec4<T> operator*(const TVec4<T>& v) const;
    TMat4<T> operator*(T f) const;
    TMat4<T> operator/(T f) const;

    TMat4<T>& operator*=(const TMat4<T>& m);
    TMat4<T>& operator*=(T f);
    TMat4<T>& operator/=(T f);

    TVec4<T> getRow(size_t j) const;
    TVec4<T> getCol(size_t i) const;

    TMat4<T> transpose() const;

    static TMat4<T> identity();
    static TMat4<T> rotate(double angle, const TVec3<T>& axis);
    static TMat4<T> translate(const TVec3<T>& v);

    static TMat4<T> ortho(T left, T right, T bottom, T top, T znear, T zfar);
    static TMat4<T> perspective(T fovy, T aspect, T znear, T zfar);
    static TMat4<T> frustum(T left, T right, T bottom, T top, T znear, T zfar);

    const T* getArray() const;
    T* getArray();

    size_t getMemSize() const;

private:
    T m_data[16];
};
////////////////////////////////////////////////////////////////////////////////
//template <typename T> std::ostream& operator<<(std::ostream& o, const TMat4<T>& m);
template <typename T> Logger& operator<<(Logger& o, const TMat4<T>& v);
////////////////////////////////////////////////////////////////////////////////
template <typename T> bool operator==(const TMat4<T>& lhs, const TMat4<T>& rhs);
template <typename T> bool operator!=(const TMat4<T>& lhs, const TMat4<T>& rhs);
////////////////////////////////////////////////////////////////////////////////
typedef TMat4<int> Mat4i;
typedef TMat4<float> Mat4f;
typedef TMat4<double> Mat4d;
////////////////////////////////////////////////////////////////////////////////
typedef Mat4d Mat4;
////////////////////////////////////////////////////////////////////////////////
//#include "mat4.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __MAT4_HPP__
