#ifndef __MAT3_HPP__
#define __MAT3_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TMat3;
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& o, TMat3<T> const& mat);
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TMat3
{
public:
    TMat3();
    TMat3(const T* v);
    TMat3(T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9);
    
    T operator()(size_t i, size_t j) const;
    T& operator()(size_t i, size_t j);
    
    TMat3 transpose() const;
    
    size_t getMemSize() const;
    
    friend std::ostream& operator<< <> (std::ostream& o, TMat3<T> const& mat);

private:
    T m_data[9];
};
////////////////////////////////////////////////////////////////////////////////
typedef TMat3<int> Mat3i;
typedef TMat3<float> Mat3;
typedef TMat3<double> Mat3d;
//#include "mat3.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __MAT3_HPP__
