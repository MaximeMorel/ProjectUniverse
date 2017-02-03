////////////////////////////////////////////////////////////////////////////////
#include "vec3.hpp"
#include "vec3.inl"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
template class ENGINE_EXPORT TVec3<int8_t>;
template class ENGINE_EXPORT TVec3<uint8_t>;
template class ENGINE_EXPORT TVec3<int32_t>;
template class ENGINE_EXPORT TVec3<uint32_t>;
template class ENGINE_EXPORT TVec3<float>;
template class ENGINE_EXPORT TVec3<double>;

template Logger& operator<<(Logger& o, const TVec3<int>& v);
template Logger& operator<<(Logger& o, const TVec3<float>& v);
template Logger& operator<<(Logger& o, const TVec3<double>& v);

template bool ENGINE_EXPORT operator==(const TVec3<double>& lhs, const TVec3<double>& rhs);
template bool ENGINE_EXPORT operator!=(const TVec3<double>& lhs, const TVec3<double>& rhs);
////////////////////////////////////////////////////////////////////////////////
