#include "common.hpp"

Vector3::Vector3()
	: x(0.0), y(0.0), z(0.0)
{ }

Vector3::Vector3(float v)
	: x(v), y(v), z(v)
{ }

Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{ }

Vector3::Vector3(const Vector2& v)
	: x(v.x), y(v.y), z(0.0)
{ }

Vector3::Vector3(const Vector3& v)
	: x(v.x), y(v.y), z(v.z)
{ }

Vector3::Vector3(const Vector4& v)
	: x(v.x), y(v.y), z(v.z)
{ }

Vector3&
Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3&
Vector3::operator=(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3&
Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3&
Vector3::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

Vector3&
Vector3::operator*=(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3&
Vector3::operator*=(const Matrix4x4& m)
{
	(*this) = m * (*this);
	return *this;
}

Vector3&
Vector3::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

bool
Vector3::operator==(const Vector3& other) const
{
	return (std::fabs(x - other.x) < std::numeric_limits<float>::epsilon()) &&
	       (std::fabs(y - other.y) < std::numeric_limits<float>::epsilon()) &&
	       (std::fabs(z - other.z) < std::numeric_limits<float>::epsilon());
}

float
Vector3::getMagnitude() const
{
	return std::fabs(this->dotProduct(*this));
}

float
Vector3::dotProduct(const Vector3& v) const
{
	return x * v.x +
	       y * v.y +
	       z * v.z;
}

Vector3
Vector3::crossProduct(const Vector3& v) const
{
	return Vector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}


Vector3
Vector3::getNormalized() const
{
	return Vector3(*this).normalize();
}

Vector3&
Vector3::normalize()
{
	float magnitude = getMagnitude();
	if(magnitude < std::numeric_limits<float>::epsilon())
		return *this;

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;

	return *this;
}

std::ostream&
operator<<(std::ostream& os, const Vector3& v)
{
	return os << v.x << '\t' << v.y << '\t' << v.z;
}
