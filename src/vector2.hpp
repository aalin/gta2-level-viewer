#ifndef VECTOR2_HPP
#define VECTOR2_HPP

struct Vector2
	: boost::addable<Vector2
	, boost::subtractable<Vector2
	, boost::multipliable<Vector2
	, boost::multipliable<Vector2, float
	, boost::dividable<Vector2
	, boost::dividable<Vector2, float
	  > > > > > >
{
	Vector2();
	Vector2(float, float);
	Vector2(const Vector2&);

	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	Vector2& operator*=(float);
	Vector2& operator*=(const Vector2&);
	Vector2& operator/=(float);
	Vector2& operator=(const Vector2&);

	float x, y;

	friend std::ostream& operator<<(std::ostream&, const Vector2&);
};

#endif

