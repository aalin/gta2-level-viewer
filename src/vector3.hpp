#ifndef VECTOR3_HPP
#define VECTOR3_HPP

struct Vector4;
class Matrix4x4;

struct Vector3
	: boost::addable<Vector3
	, boost::subtractable<Vector3
	, boost::multipliable<Vector3
	, boost::multipliable<Vector3, float
	, boost::multipliable<Matrix4x4
	, boost::dividable<Vector3
	, boost::dividable<Vector3, float
	  > > > > > > >
{
	Vector3();
	Vector3(float);
	Vector3(float, float, float);
	Vector3(const Vector2&);
	Vector3(const Vector2&, float);
	Vector3(const Vector3&);
	Vector3(const Vector4&);

	Vector3& operator+=(const Vector3&);
	Vector3& operator-=(const Vector3&);
	Vector3& operator*=(float);
	Vector3& operator*=(const Vector3&);
	Vector3& operator*=(const Matrix4x4&);
	Vector3& operator/=(float);
	Vector3& operator=(const Vector3&);

	Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	bool operator==(const Vector3&) const;

	float getMagnitude() const;
	float dotProduct(const Vector3& v) const;
	Vector3 crossProduct(const Vector3& v) const;

	Vector3 getNormalized() const;
	Vector3& normalize();

	float x, y, z;

	friend std::ostream& operator<<(std::ostream&, const Vector3&);
};

#endif

