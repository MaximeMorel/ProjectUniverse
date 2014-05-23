////////////////////////////////////////////////////////////////////////////////
#include "mat3.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat3<T>::TMat3()
: m_data{0, 0, 0, 0, 0, 0, 0, 0, 0}
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
T TMat3<T>::operator()(size_t i, size_t j) const
{
    return m_data[i + (j*3)];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T& TMat3<T>::operator()(size_t i, size_t j)
{
    return m_data[i + (j*3)];
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
size_t TMat3<T>::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& o, TMat3<T> const& mat)
{
    return o << "[ " << mat.m_data[0] << ", " << mat.m_data[1] << ", " << mat.m_data[2] << " ]\n" <<
                "[ " << mat.m_data[3] << ", " << mat.m_data[4] << ", " << mat.m_data[5] << " ]\n" <<
                "[ " << mat.m_data[6] << ", " << mat.m_data[7] << ", " << mat.m_data[8] << " ]\n";
}
////////////////////////////////////////////////////////////////////////////////
template class TMat3<int>;
template class TMat3<float>;
template class TMat3<double>;
////////////////////////////////////////////////////////////////////////////////
