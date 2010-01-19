#include "common.hpp"

Vector4::Vector4()
	: x(0.0), y(0.0), z(0.0), w(0.0)
{ }

Vector4::Vector4(float v)
	: x(v), y(v), z(v), w(v)
{ }

Vector4::Vector4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{ }

Vector4::Vector4(const Vector2& v, float z, float w)
	: x(v.x), y(v.y), z(z), w(w)
{ }

Vector4::Vector4(const Vector3& v)
	: x(v.x), y(v.y), z(v.z), w(0)
{ }

Vector4::Vector4(const Vector3& v, float w)
	: x(v.x), y(v.y), z(v.z), w(w)
{ }

Vector4::Vector4(const Vector4& v)
	: x(v.x), y(v.y), z(v.z), w(v.w)
{ }

Vector4&
Vector4::operator+=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4&
Vector4::operator-=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4&
Vector4::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

Vector4&
Vector4::operator*=(const Vector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

Vector4&
Vector4::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;
	return *this;
}

Vector4&
Vector4::operator=(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

bool
Vector4::operator==(const Vector4& other) const
{
	return (std::fabs(x - other.x) < std::numeric_limits<float>::epsilon()) &&
	       (std::fabs(y - other.y) < std::numeric_limits<float>::epsilon()) &&
	       (std::fabs(z - other.z) < std::numeric_limits<float>::epsilon()) &&
	       (std::fabs(w - other.w) < std::numeric_limits<float>::epsilon());
}

float
Vector4::getMagnitude() const
{
	return std::fabs(this->dotProduct(*this));
}

float
Vector4::dotProduct(const Vector4& v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z) + (w + v.w);
}

Vector4
Vector4::getNormalized() const
{
	return Vector4(*this).normalize();
}

Vector4&
Vector4::normalize()
{
	float magnitude = getMagnitude();
	if(magnitude < std::numeric_limits<float>::epsilon())
		return *this;

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
	w /= magnitude;

	return *this;
}

std::ostream&
operator <<(std::ostream& os, const Vector4& v)
{
	return os << v.x << '\t' << v.y << '\t' << v.z << '\t' << v.w;
}
