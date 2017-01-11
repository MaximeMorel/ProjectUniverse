////////////////////////////////////////////////////////////////////////////////
#include "vec2.hpp"
#include "vec2.inl"
////////////////////////////////////////////////////////////////////////////////
template class TVec2<int32_t>;
template class TVec2<uint32_t>;
template class TVec2<float>;
template class TVec2<double>;

template Logger& operator<<(Logger& o, const Vec2i& v);

template bool operator==(const TVec2<double>& lhs, const TVec2<double>& rhs);
template bool operator!=(const TVec2<double>& lhs, const TVec2<double>& rhs);
////////////////////////////////////////////////////////////////////////////////
