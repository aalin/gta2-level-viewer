#ifndef MATH_HPP
#define MATH_HPP

namespace Math {
	const float PI = 3.14159265358979;
	inline float degreesToRadians(float degrees)
	{
		return degrees * Math::PI / 180.0;
	}

	inline float radiansToDegrees(float radians)
	{
		return radians * 180.0 / Math::PI;
	}
}

#endif

