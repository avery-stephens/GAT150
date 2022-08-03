//#pragma once

#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

namespace math
{
	const float pi = 3.14159265359f; //180
	const float twoPi = 6.28318530718f; //360
	const float HalfPi = 1.57079632679f; //90

	inline float DegtoRad(float degrees)
	{
		return degrees * (pi / 180);
	}
	
	inline float RadtoDeg(float radians)
	{
		return radians * (180 / pi);
	}

	int sqr(int v);
	inline int half(int v) { return v / 2; }
}
#endif // __MATH_UTILS_H__
