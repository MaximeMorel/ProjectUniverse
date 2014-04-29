#ifndef __VEC2_HPP__
#define __VEC2_HPP__
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TVec2
{
public:
	TVec2();
	TVec2(const T& x, const T& y);
    TVec2(const TVec2<T>& vec);

	T x, y;
};
////////////////////////////////////////////////////////////////////////////////
typedef TVec2<int> Vec2i;
typedef TVec2<float> Vec2;
typedef TVec2<double> Vec2d;
////////////////////////////////////////////////////////////////////////////////
#endif // __VEC2_HPP__
