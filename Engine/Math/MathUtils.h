#pragma once
#include <cmath>

#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

namespace math
{
	constexpr float pi = 3.14159265359f; //180
	constexpr float twoPi = 6.28318530718f; //360
	constexpr float HalfPi = 1.57079632679f; //90

	constexpr inline float DegtoRad(float degrees)
	{
		return degrees * (pi / 180);
	}
	
	constexpr inline float RadtoDeg(float radians)
	{
		return radians * (180 / pi);
	}

	template <typename T>
	T Clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;

		return value;
	}

	template <typename T>
	T Lerp(T min, T max, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);

		return min + ((max - min) * t);
	}

	template <typename T>
	T Normalize(T value, T min, T max)
	{
		return (value - min) / (max - min);
	}

	template <typename T>
	T Remap(T value, T inMin, T inMax, T outMin, T outMax)
	{
		return Lerp(outMin, outMax, Normalize(value, inMin, inMax));
	}

	template <typename T>
	T mod(T numerator, T denominator)
	{
		return std::fmod(numerator, denominator);
	}

	template <>
	inline int mod(int numerator, int denominator)
	{
		return numerator % denominator;
	}

	template <typename T>
	T Wrap(T value, T min, T max)
	{
		if (value < min) return max - mod((min - value), (max - min));
		if (value > max) return min + mod((value - min), (max - min));

		return value;
	}
}
#endif // __MATH_UTILS_H__
