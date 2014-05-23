#ifndef __MAT4_HPP__
#define __MAT4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "vec4.hpp"
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TMat4;
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& o, const TMat4<T>& m);
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TMat4
{
public:
    TMat4();
    TMat4(const T* v);
    TMat4(T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9, T v10, T v11, T v12, T v13, T v14, T v15, T v16);
    
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
    
    TMat4 transpose() const;
    
    size_t getMemSize() const;
    
    friend std::ostream& operator<< <> (std::ostream& o, const TMat4<T>& m);

private:
    T m_data[16];
};
////////////////////////////////////////////////////////////////////////////////
typedef TMat4<int> Mat4i;
typedef TMat4<float> Mat4;
typedef TMat4<double> Mat4d;
////////////////////////////////////////////////////////////////////////////////
#include "mat4.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __MAT4_HPP__
