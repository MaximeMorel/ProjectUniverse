////////////////////////////////////////////////////////////////////////////////
#include "mat3.hpp"
#include <stdexcept>
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T>::TMat3()
: m_data{0, 0, 0, 0, 0, 0, 0, 0, 0}
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T>::TMat3(T f)
: m_data{f, 0, 0, 0, f, 0, 0, 0, f}
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T>::TMat3(const T* v)
: m_data{*(v+0), *(v+1), *(v+2), *(v+3), *(v+4), *(v+5), *(v+6), *(v+7), *(v+8)}
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T>::TMat3(T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9)
: m_data{v1, v2, v3, v4, v5, v6, v7, v8, v9}
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T TMat3<T>::operator[](size_t i) const
{
    return m_data[i];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T& TMat3<T>::operator[](size_t i)
{
    return m_data[i];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T TMat3<T>::operator()(size_t i, size_t j) const
{
    return m_data[i + (j*3)];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T& TMat3<T>::operator()(size_t i, size_t j)
{
    return m_data[i + (j*3)];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T> TMat3<T>::operator*(const TMat3<T>& m) const
{
    TMat3<T> res;
    for(size_t i=0; i<3; ++i)
    {
        for(size_t j=0; j<3; ++j)
        {
            T& val = res(i,j);
            for(size_t k=0; k<3; ++k)
            {
                val += (*this)(i,k) * m(k,j);
            }
        }
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec3<T> TMat3<T>::operator*(const TVec3<T>& v) const
{
    TVec3<T> res;
    for(size_t i=0; i<3; ++i)
    {
        T& val = res[i];
        for(size_t k=0; k<3; ++k)
        {
            val += (*this)(i,k) * v[k];
        }
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T> TMat3<T>::operator*(T f) const
{
    TMat3<T> res;
    for(size_t i=0; i<9; ++i)
    {
        res.m_data[i] = m_data[i]*f;
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T> TMat3<T>::operator/(T f) const
{
    TMat3<T> res;
    for(size_t i=0; i<9; ++i)
    {
        res.m_data[i] = m_data[i]/f;
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T> TMat3<T>::transpose() const
{
    return TMat3<T>(m_data[0], m_data[3], m_data[6],
                    m_data[1], m_data[4], m_data[7],
                    m_data[2], m_data[5], m_data[8]);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T TMat3<T>::trace() const
{
    return m_data[0] + m_data[4] + m_data[8];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T TMat3<T>::determinant() const
{
    return m_data[0]*m_data[4]*m_data[8] + m_data[1]*m_data[5]*m_data[6] +
           m_data[2]*m_data[3]*m_data[7] - m_data[2]*m_data[4]*m_data[6] -
           m_data[1]*m_data[3]*m_data[8] - m_data[0]*m_data[5]*m_data[7];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T> TMat3<T>::inverse() const
{
    T det = determinant();
    if(det == 0)
    {
        throw std::domain_error("matrix determinant is zero");
    }
    const T* m = m_data;
    return TMat3<T>(m[8]*m[4]-m[7]*m[5], -(m[8]*m[1]-m[7]*m[2]), m[5]*m[1]-m[4]*m[2],
                    -(m[8]*m[3]-m[6]*m[5]), m[8]*m[0]-m[6]*m[2], -(m[5]*m[0]-m[3]*m[2]),
                    m[7]*m[3]-m[6]*m[4], -(m[7]*m[0]-m[6]*m[1]), m[4]*m[0]-m[3]*m[1])*(1.0/det);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
size_t TMat3<T>::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& o, TMat3<T> const& mat)
{
    return o << "[ " << mat[0] << ", " << mat[1] << ", " << mat[2] << " ]\n" <<
                "[ " << mat[3] << ", " << mat[4] << ", " << mat[5] << " ]\n" <<
                "[ " << mat[6] << ", " << mat[7] << ", " << mat[8] << " ]\n";
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
Logger& operator<<(Logger& o, TMat3<T> const& mat)
{
    return o << "[ " << mat[0] << ", " << mat[1] << ", " << mat[2] << " ]\n" <<
                "[ " << mat[3] << ", " << mat[4] << ", " << mat[5] << " ]\n" <<
                "[ " << mat[6] << ", " << mat[7] << ", " << mat[8] << " ]\n";
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool operator==(const TMat3<T>& lhs, const TMat3<T>& rhs)
{
    for(int i=0; i<9; ++i)
    {
        if(lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool operator!=(const TMat3<T>& lhs, const TMat3<T>& rhs)
{
    for(int i=0; i<9; ++i)
    {
        if(lhs[i] != rhs[i])
        {
            return true;
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
//template class TMat3<int>;
//template class TMat3<float>;
//template class TMat3<double>;
////////////////////////////////////////////////////////////////////////////////
