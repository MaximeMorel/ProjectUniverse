////////////////////////////////////////////////////////////////////////////////
#include "vec2.hpp"
#include "vec2.inl"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
template class ENGINE_EXPORT TVec2<int32_t>;
template class ENGINE_EXPORT TVec2<uint32_t>;
template class ENGINE_EXPORT TVec2<float>;
template class ENGINE_EXPORT TVec2<double>;

template Logger ENGINE_EXPORT & operator<<(Logger& o, const Vec2i& v);

template bool ENGINE_EXPORT operator==(const TVec2<double>& lhs, const TVec2<double>& rhs);
template bool ENGINE_EXPORT operator!=(const TVec2<double>& lhs, const TVec2<double>& rhs);
////////////////////////////////////////////////////////////////////////////////
