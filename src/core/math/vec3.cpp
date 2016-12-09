////////////////////////////////////////////////////////////////////////////////
#include "vec3.hpp"
#include "vec3.inl"
////////////////////////////////////////////////////////////////////////////////
template class TVec3<int>;
template class TVec3<float>;
template class TVec3<double>;
template class TVec3<uint8_t>;

template Logger& operator<<(Logger& o, const TVec3<int>& v);
template Logger& operator<<(Logger& o, const TVec3<float>& v);
template Logger& operator<<(Logger& o, const TVec3<double>& v);

template bool operator==(const TVec3<double>& lhs, const TVec3<double>& rhs);
template bool operator!=(const TVec3<double>& lhs, const TVec3<double>& rhs);
////////////////////////////////////////////////////////////////////////////////
