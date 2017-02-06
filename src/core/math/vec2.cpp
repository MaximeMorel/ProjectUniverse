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

template bool ENGINE_EXPORT operator==(const Vec2i& lhs, const Vec2i& rhs);
template bool ENGINE_EXPORT operator!=(const Vec2i& lhs, const Vec2i& rhs);

template bool ENGINE_EXPORT operator==(const Vec2ui& lhs, const Vec2ui& rhs);
template bool ENGINE_EXPORT operator!=(const Vec2ui& lhs, const Vec2ui& rhs);

template bool ENGINE_EXPORT operator==(const Vec2f& lhs, const Vec2f& rhs);
template bool ENGINE_EXPORT operator!=(const Vec2f& lhs, const Vec2f& rhs);

template bool ENGINE_EXPORT operator==(const Vec2d& lhs, const Vec2d& rhs);
template bool ENGINE_EXPORT operator!=(const Vec2d& lhs, const Vec2d& rhs);
////////////////////////////////////////////////////////////////////////////////
