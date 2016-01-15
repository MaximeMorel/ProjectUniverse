////////////////////////////////////////////////////////////////////////////////
#include "mat4.hpp"
#include <cmath>
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
    return m_data[i + (j*4)];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T& TMat4<T>::operator()(size_t i, size_t j)
{
    return m_data[i + (j*4)];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::operator*(const TMat4<T>& m) const
{
    TMat4<T> res;
    for(size_t i=0; i<4; ++i)
    {
        for(size_t j=0; j<4; ++j)
        {
            T& val = res(i,j);
            for(size_t k=0; k<4; ++k)
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
    for(size_t i=0; i<4; ++i)
    {
        T& val = res[i];
        for(size_t k=0; k<4; ++k)
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
    for(size_t i=0; i<16; ++i)
    {
        res.m_data[i] = m_data[i]*f;
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::operator/(T f) const
{
    TMat4<T> res;
    for(size_t i=0; i<16; ++i)
    {
        res.m_data[i] = m_data[i]/f;
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
    for(size_t i=0; i<16; ++i)
    {
        m_data[i] *= f;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T>& TMat4<T>::operator/=(T f)
{
    return operator*=(1.0/f);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TMat4<T>::getRow(size_t j) const
{
    return TVec4<T>(m_data[(j*4)+0], m_data[(j*4)+1], m_data[(j*4)+2], m_data[(j*4)+3]);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TMat4<T>::getCol(size_t i) const
{
    return TVec4<T>(m_data[i], m_data[4+i], m_data[8+i], m_data[12+i]);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::transpose() const
{
    return TMat4<T>(m_data[0], m_data[4], m_data[8], m_data[12],
                    m_data[1], m_data[5], m_data[9], m_data[13],
                    m_data[2], m_data[6], m_data[10], m_data[14],
                    m_data[3], m_data[7], m_data[11], m_data[15]);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::rotate(double angle, const TVec3<T>& axis)
{
    TMat4<T> res;

    TVec3<T> axisn = axis.normalize();

    const double s = sin(angle*(M_PI/180.0));
    const double c = cos(angle*(M_PI/180.0));

    res.m_data[0] = axisn.x * axisn.x + (1.0 - axisn.x * axisn.x) * c;
    res.m_data[1] = axisn.x * axisn.y * (1.0 - c) - (axisn.z * s);
    res.m_data[2] = axisn.x * axisn.z * (1.0 - c) + (axisn.y * s);
    res.m_data[3] = 0.0;

    res.m_data[4] = axisn.x * axisn.y * (1.0 - c) + (axisn.z * s);
    res.m_data[5] = axisn.y * axisn.y + (1.0 - axisn.y * axisn.y) * c;
    res.m_data[6] = axisn.y * axisn.z * (1.0 - c) - (axisn.x * s);
    res.m_data[7] = 0.0;

    res.m_data[8] = axisn.x * axisn.z * (1.0 - c) - (axisn.y * s);
    res.m_data[9] = axisn.y * axisn.z * (1.0 - c) + (axisn.x * s);
    res.m_data[10] = axisn.z * axisn.z + (1.0 - axisn.z * axisn.z) * c;
    res.m_data[11] = 0.0;

    res.m_data[12] = 0.0;
    res.m_data[13] = 0.0;
    res.m_data[14] = 0.0;
    res.m_data[15] = 1.0;

    return res;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::identity()
{
    return TMat4<T>(1);
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
TMat4<T> TMat4<T>::ortho(T left, T right, T bottom, T top, T znear, T zfar)
{
    T tx = -(right+left)/(right-left);
    T ty = -(top+bottom)/(top-bottom);
    T tz = -(zfar+znear)/(zfar-znear);

    return TMat4<T>(2.0/(right-left), 0.0, 0.0, 0.0,
                    0.0, 2.0/(top-bottom), 0.0, 0.0,
                    0.0, 0.0, -2.0/(zfar-znear), 0.0,
                    tx, ty, tz, 1.0);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::perspective(T fovy, T aspect, T znear, T zfar)
{
    T ymax = znear*tan(fovy*M_PI/360.0);
    T ymin = -ymax;
    T xmin = ymin*aspect;
    T xmax = ymax*aspect;

    return TMat4<T>::frustum(xmin, xmax, ymin, ymax, znear, zfar);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TMat4<T> TMat4<T>::frustum(T left, T right, T bottom, T top, T znear, T zfar)
{
    T x = 2.0*znear/(right-left);
    T y = 2.0*znear/(top-bottom);
    T a = (right+left)/(right-left);
    T b = (top+bottom)/(top-bottom);
    T c = -(zfar+znear)/(zfar-znear);
    T d = -2.0*zfar*znear/(zfar-znear);

    return TMat4<T>(x, 0.0, 0.0, 0.0,
                    0.0, y, 0.0, 0.0,
                    a, b, c, -1.0,
                    0.0, 0.0, d, 0.0);
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
/*template <typename T>
std::ostream& operator<<(std::ostream& o, const TMat4<T>& m)
{
    return o << "[ " << m[0] << ", " << m[1] << ", " << m[2] << ", " << m[3] << " ]\n" <<
                "[ " << m[4] << ", " << m[5] << ", " << m[6] << ", " << m[7] << " ]\n" <<
                "[ " << m[8] << ", " << m[9] << ", " << m[10] << ", " << m[11] << " ]\n" <<
                "[ " << m[12] << ", " << m[13] << ", " << m[14] << ", " << m[15] << " ]\n";
}*/
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
    for(int i=0; i<16; ++i)
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
bool operator!=(const TMat4<T>& lhs, const TMat4<T>& rhs)
{
    for(int i=0; i<16; ++i)
    {
        if(lhs[i] != rhs[i])
        {
            return true;
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
//template class TMat4<int>;
//template class TMat4<float>;
//template class TMat4<double>;
////////////////////////////////////////////////////////////////////////////////
