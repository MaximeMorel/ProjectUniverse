////////////////////////////////////////////////////////////////////////////////
#include "mat4.hpp"
#include <cmath>
#ifndef M_PI
# define M_PI   3.14159265358979323846  /* pi */
#endif // M_PI
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T>::TMat4()
    : m_data{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T>::TMat4(T f)
    : m_data{f, 0, 0, 0, 0, f, 0, 0, 0, 0, f, 0, 0, 0, 0, f}
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T>::TMat4(const T* v)
    : m_data{*(v+0), *(v+1), *(v+2), *(v+3), *(v+4), *(v+5), *(v+6), *(v+7), *(v+8), *(v+9), *(v+10), *(v+11), *(v+12), *(v+13), *(v+14), *(v+15)}
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T>::TMat4(T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9, T v10, T v11, T v12, T v13, T v14, T v15, T v16)
    : m_data{v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16}
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T TMat4<T>::operator[](size_t i) const
{
    return m_data[i];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T& TMat4<T>::operator[](size_t i)
{
    return m_data[i];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T TMat4<T>::operator()(size_t i, size_t j) const
{
    return m_data[i + (j * 4)];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T& TMat4<T>::operator()(size_t i, size_t j)
{
    return m_data[i + (j * 4)];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::operator*(const TMat4<T>& m) const
{
    TMat4<T> res;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            T& val = res(i,j);
            for (size_t k = 0; k < 4; ++k)
            {
                val += (*this)(i,k) * m(k,j);
            }
        }
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TMat4<T>::operator*(const TVec4<T>& v) const
{
    TVec4<T> res;
    for (size_t i = 0; i < 4; ++i)
    {
        T& val = res[i];
        for (size_t k = 0; k < 4; ++k)
        {
            val += (*this)(i,k) * v[k];
        }
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::operator*(T f) const
{
    TMat4<T> res;
    for (size_t i = 0; i < 16; ++i)
    {
        res.m_data[i] = m_data[i] * f;
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::operator/(T f) const
{
    TMat4<T> res;
    for (size_t i = 0; i < 16; ++i)
    {
        res.m_data[i] = m_data[i] / f;
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T>& TMat4<T>::operator*=(const TMat4<T>& m)
{
    *this = operator*(m);
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T>& TMat4<T>::operator*=(T f)
{
    for (size_t i = 0; i < 16; ++i)
    {
        m_data[i] *= f;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T>& TMat4<T>::operator/=(T f)
{
    return operator*=(static_cast<T>(1) / f);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TMat4<T>::getRow(size_t j) const
{
    return TVec4<T>(m_data[(j * 4) + 0], m_data[(j * 4) + 1], m_data[(j * 4) + 2], m_data[(j * 4) + 3]);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TMat4<T>::getCol(size_t i) const
{
    return TVec4<T>(m_data[i], m_data[4 + i], m_data[8 + i], m_data[12 + i]);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::transpose() const
{
    return TMat4<T>(m_data[0], m_data[4], m_data[8],  m_data[12],
                    m_data[1], m_data[5], m_data[9],  m_data[13],
                    m_data[2], m_data[6], m_data[10], m_data[14],
                    m_data[3], m_data[7], m_data[11], m_data[15]);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::rotate(double angle, const TVec3<T>& axis)
{
    TMat4<T> res;

    TVec3<T> axisn = axis.normalize();

    constexpr T c0 = static_cast<T>(0);
    constexpr T c1 = static_cast<T>(1);
    constexpr T cpi180 = static_cast<T>(M_PI) / static_cast<T>(180);

    const T s = sin(angle * cpi180);
    const T c = cos(angle * cpi180);

    res.m_data[0]  = axisn.x * axisn.x + (c1 - axisn.x * axisn.x) * c;
    res.m_data[1]  = axisn.x * axisn.y * (c1 - c) - (axisn.z * s);
    res.m_data[2]  = axisn.x * axisn.z * (c1 - c) + (axisn.y * s);
    res.m_data[3]  = c0;

    res.m_data[4]  = axisn.x * axisn.y * (c1 - c) + (axisn.z * s);
    res.m_data[5]  = axisn.y * axisn.y + (c1 - axisn.y * axisn.y) * c;
    res.m_data[6]  = axisn.y * axisn.z * (c1 - c) - (axisn.x * s);
    res.m_data[7]  = c0;

    res.m_data[8]  = axisn.x * axisn.z * (c1 - c) - (axisn.y * s);
    res.m_data[9]  = axisn.y * axisn.z * (c1 - c) + (axisn.x * s);
    res.m_data[10] = axisn.z * axisn.z + (c1 - axisn.z * axisn.z) * c;
    res.m_data[11] = c0;

    res.m_data[12] = c0;
    res.m_data[13] = c0;
    res.m_data[14] = c0;
    res.m_data[15] = c1;

    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::identity()
{
    return TMat4<T>(static_cast<T>(1));
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::translate(const TVec3<T>& v)
{
    TMat4<T> res = TMat4<T>::identity();

    res.m_data[12] = v.x;
    res.m_data[13] = v.y;
    res.m_data[14] = v.z;

    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::scale(const TVec3<T>& v)
{
    TMat4<T> res;

    res.m_data[0] = v.x;
    res.m_data[5] = v.y;
    res.m_data[10] = v.z;
    res.m_data[15] = static_cast<T>(1);

    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::ortho(T left, T right, T bottom, T top, T znear, T zfar)
{
    T tx = -(right + left) / (right - left);
    T ty = -(top + bottom) / (top - bottom);
    T tz = -(zfar + znear) / (zfar - znear);

    constexpr T c0 = static_cast<T>(0);
    constexpr T c1 = static_cast<T>(1);
    constexpr T c2 = static_cast<T>(2);

    return TMat4<T>(c2 / (right - left), c0, c0, c0,
                    c0, c2 / (top - bottom), c0, c0,
                    c0, c0, -c2 / (zfar - znear), c0,
                    tx, ty, tz, c1);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::perspective(T fovy, T aspect, T znear, T zfar)
{
    T ymax = znear * tan(fovy * T(M_PI) / T(360));
    T ymin = -ymax;
    T xmin = ymin * aspect;
    T xmax = ymax * aspect;

    return TMat4<T>::frustum(xmin, xmax, ymin, ymax, znear, zfar);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::frustum(T left, T right, T bottom, T top, T znear, T zfar)
{
    constexpr T c0 = static_cast<T>(0);
    constexpr T c1 = static_cast<T>(1);
    constexpr T c2 = static_cast<T>(2);

    T x = c2 * znear / (right - left);
    T y = c2 * znear / (top - bottom);
    T a = (right + left) / (right - left);
    T b = (top + bottom) / (top - bottom);
    T c = -(zfar + znear) / (zfar - znear);
    T d = -c2 * zfar * znear / (zfar - znear);

    return TMat4<T>(x , c0, c0,  c0,
                    c0,  y, c0,  c0,
                     a,  b,  c, -c1,
                    c0, c0,  d,  c0);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
const T* TMat4<T>::getArray() const
{
    return m_data;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T* TMat4<T>::getArray()
{
    return m_data;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
size_t TMat4<T>::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
Logger& operator<<(Logger& o, const TMat4<T>& m)
{
    return o << "[ " << m[0] << ", " << m[1] << ", " << m[2] << ", " << m[3] << " ]\n" <<
                "[ " << m[4] << ", " << m[5] << ", " << m[6] << ", " << m[7] << " ]\n" <<
                "[ " << m[8] << ", " << m[9] << ", " << m[10] << ", " << m[11] << " ]\n" <<
                "[ " << m[12] << ", " << m[13] << ", " << m[14] << ", " << m[15] << " ]\n";
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool operator==(const TMat4<T>& lhs, const TMat4<T>& rhs)
{
    for (int i = 0; i < 16; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool operator!=(const TMat4<T>& lhs, const TMat4<T>& rhs)
{
    for (int i = 0; i < 16; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return true;
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
