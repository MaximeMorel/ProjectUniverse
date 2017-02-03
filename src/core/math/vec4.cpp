////////////////////////////////////////////////////////////////////////////////
#include "vec4.hpp"
#include "vec4.inl"
////////////////////////////////////////////////////////////////////////////////
template class ENGINE_EXPORT TVec4<int>;
template class ENGINE_EXPORT TVec4<float>;
template class ENGINE_EXPORT TVec4<double>;
template class ENGINE_EXPORT TVec4<uint8_t>;

template Logger& operator<<(Logger& o, const TVec4<int>& v);
template Logger& operator<<(Logger& o, const TVec4<float>& v);
template Logger& operator<<(Logger& o, const TVec4<double>& v);

template bool ENGINE_EXPORT operator==(const TVec4<double>& lhs, const TVec4<double>& rhs);
template bool ENGINE_EXPORT operator!=(const TVec4<double>& lhs, const TVec4<double>& rhs);
////////////////////////////////////////////////////////////////////////////////
