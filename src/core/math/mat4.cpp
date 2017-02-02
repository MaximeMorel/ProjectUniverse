////////////////////////////////////////////////////////////////////////////////
#include "mat4.hpp"
#include "mat4.inl"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
template class ENGINE_EXPORT TMat4<int>;
template class ENGINE_EXPORT TMat4<float>;
template class ENGINE_EXPORT TMat4<double>;

template bool operator==(const TMat4<double>& lhs, const TMat4<double>& rhs);
template bool operator!=(const TMat4<double>& lhs, const TMat4<double>& rhs);
////////////////////////////////////////////////////////////////////////////////
