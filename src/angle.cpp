#include "common.hpp"

Angle::Angle(float value)
	: _value(value)
{ }

Angle::Angle()
{
	_value = 0.0;
}

Angle::~Angle()
{ }

float
Angle::convert(const Angle& other) const
{
	return other.value() * getFullCircle() / other.getFullCircle();
}

Radians::Radians(const Angle& other)
{
	_value = convert(other);
}

Degrees::Degrees(const Angle& other)
{
	_value = convert(other);
}

