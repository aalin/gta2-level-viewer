#ifndef VECTOR4_HPP
#define VECTOR4_HPP

struct Vector4 {
	Vector4();
	Vector4(float);
	Vector4(float, float, float, float);
	Vector4(const Vector2&);
	Vector4(const Vector2&, float, float = 1.0);
	Vector4(const Vector3&);
	Vector4(const Vector3&, float);
	Vector4(const Vector4&);

	float& operator[](int);
	float operator()(int) const;

	Vector4& operator+=(const Vector4&);
	Vector4& operator-=(const Vector4&);
	Vector4& operator*=(float);
	Vector4& operator*=(const Vector4&);
	Vector4& operator/=(float);
	Vector4& operator=(const Vector4&);
	bool operator==(const Vector4&) const;

	float getMagnitude() const;
	float dotProduct(const Vector4& v) const;

	Vector4 getNormalized() const;
	Vector4& normalize();

	float x, y, z, w;

	friend std::ostream& operator<<(std::ostream&, const Vector4&);
};

#endif

