#include "common.hpp"

Vector2::Vector2()
	: x(0.0), y(0.0)
{ }

Vector2::Vector2(float new_x, float new_y)
	: x(new_x), y(new_y)
{ }

Vector2::Vector2(const Vector2& v)
	: x(v.x), y(v.y)
{ }

Vector2&
Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2&
Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2&
Vector2::operator*=(float f)
{
	x *= f;
	y *= f;
	return *this;
}

Vector2&
Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2&
Vector2::operator/=(float f)
{
	x /= f;
	y /= f;
	return *this;
}

Vector2&
Vector2::operator=(const Vector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

std::ostream&
operator<<(std::ostream& os, const Vector2& v)
{
	return os << v.x << '\t' << v.y;
}
