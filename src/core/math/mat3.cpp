////////////////////////////////////////////////////////////////////////////////
#include "mat3.hpp"
#include "mat3.inl"
////////////////////////////////////////////////////////////////////////////////
template class ENGINE_EXPORT TMat3<int>;
template class ENGINE_EXPORT TMat3<float>;
template class ENGINE_EXPORT TMat3<double>;

template bool ENGINE_EXPORT operator==(const TMat3<double>& lhs, const TMat3<double>& rhs);
template bool ENGINE_EXPORT operator!=(const TMat3<double>& lhs, const TMat3<double>& rhs);
////////////////////////////////////////////////////////////////////////////////
