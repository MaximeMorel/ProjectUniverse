////////////////////////////////////////////////////////////////////////////////
#include "vec4.hpp"
#include <cmath>
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T>::TVec4()
: x(0), y(0), z(0), w(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T>::TVec4(const T& x, const T& y, const T& z, const T& w)
: x(x), y(y), z(z), w(w)
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T>::TVec4(const TVec3<T>& v, const T& w)
: x(v.x), y(v.y), z(v.z), w(w)
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T TVec4<T>::operator[](size_t i) const
{
    return *(((T*)&x)+i);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T& TVec4<T>::operator[](size_t i)
{
    return *(((T*)&x)+i);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T TVec4<T>::dot(const TVec4<T>& v) const
{
    return x*v.x + y*v.y + z*v.z + w*v.w;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec3<T> TVec4<T>::cross(const TVec4<T>& v) const
{
    return TVec3<T>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T TVec4<T>::length() const
{
    return sqrt(x*x + y*y + z*z + w*w);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T TVec4<T>::sqrLength() const
{
    return x*x + y*y + z*z + w*w;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TVec4<T>::normalize() const
{
    T len = length();
    return TVec4<T>(x/len, y/len, z/len, w/len);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TVec4<T>::operator+(const TVec4& v) const
{
    return TVec3<T>(x+v.x, y+v.y, z+v.z, w+v.w);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TVec4<T>::operator-(const TVec4& v) const
{
    return TVec4<T>(x-v.x, y-v.y, z-v.z, w-v.w);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TVec4<T>::operator*(T f) const
{
    return TVec4<T>(x*f, y*f, z*f, w*f);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TVec4<T>::operator/(T f) const
{
    return TVec4<T>(x/f, y/f, z/f, w/f);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TVec4<T> TVec4<T>::operator-() const
{
    return TVec4<T>(-x, -y, -z, -w);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
size_t TVec4<T>::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& o, const TVec4<T>& v)
{
    return o << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}
////////////////////////////////////////////////////////////////////////////////
/*template class TVec4<int>;
template class TVec4<float>;
template class TVec4<double>;*/
////////////////////////////////////////////////////////////////////////////////
