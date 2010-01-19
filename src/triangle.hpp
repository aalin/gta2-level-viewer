#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

class Triangle {
	public:
		Vector3 a;
		Vector3 b;
		Vector3 c;

		Vector3 normal()
		{
			return (a - b).crossProduct(b - c).normalize();
		}

		Triangle& translate(const Vector3& v)
		{
			Matrix4x4 m(Matrix4x4::translation(v));
			a *= m;
			b *= m;
			c *= m;
			return *this;
		}

		Triangle& rotateX(const Angle& angle)
		{
			Matrix4x4 m(Matrix4x4::rotationX(angle));
			a *= m;
			b *= m;
			c *= m;
			return *this;
		}

		Triangle& rotateY(const Angle& angle)
		{
			Matrix4x4 m(Matrix4x4::rotationY(angle));
			a *= m;
			b *= m;
			c *= m;
			return *this;
		}

		Triangle& rotateZ(const Angle& angle)
		{
			Matrix4x4 m(Matrix4x4::rotationZ(angle));
			a *= m;
			b *= m;
			c *= m;
			return *this;
		}
};

#endif

