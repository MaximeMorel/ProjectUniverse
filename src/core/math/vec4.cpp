////////////////////////////////////////////////////////////////////////////////
#include "vec4.hpp"
#include "vec4.inl"
////////////////////////////////////////////////////////////////////////////////
template class TVec4<int>;
template class TVec4<float>;
template class TVec4<double>;

template Logger& operator<<(Logger& o, const TVec4<int>& v);
template Logger& operator<<(Logger& o, const TVec4<float>& v);
template Logger& operator<<(Logger& o, const TVec4<double>& v);

template bool operator==(const TVec4<double>& lhs, const TVec4<double>& rhs);
template bool operator!=(const TVec4<double>& lhs, const TVec4<double>& rhs);
////////////////////////////////////////////////////////////////////////////////
