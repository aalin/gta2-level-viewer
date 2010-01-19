#define BOOST_ENABLE_ASSERT_HANDLER
#include <boost/assert.hpp>

#include "common.hpp"

namespace boost {
	void assertion_failed(char const *expr, char const *function, char const *file, long line)
	{
		std::cout << "FAIL!" << std::endl <<
		             "\texpr: " << expr << std::endl <<
		             "\tfunction " << function << " in " << file << ":" << line << std::endl;
	}
};

void testAngles()
{
	std::cout << "1 radians to degrees" << std::endl;
	std::cout << Degrees(Radians(1)).value() << std::endl;
	std::cout << "23 degrees to radians" << std::endl;
	std::cout << Radians(Degrees(23)).value() << std::endl;
}

void testVector3()
{
	// Cross product
	BOOST_ASSERT(Vector3(1, 2, 3).crossProduct(Vector3(4, 5, 6)) == Vector3(-3, 6, -3));
	BOOST_ASSERT(Vector3(3, 0, 0).crossProduct(Vector3(0, 2, 0)) == Vector3(0, 0, 6));
}

void testMatrix3x3()
{
	Matrix3x3 m1(
		Vector3(2, 2, 1),
		Vector3(1, 2, 3),
		Vector3(2, 2, 2)
	);

	Matrix3x3 m2(
		Vector3(2, 3, 2),
		Vector3(5, 6, 7),
		Vector3(2, 3, 2).crossProduct(Vector3(5, 6, 7))
	);

	Matrix3x3 m3(
		Vector3(1, 2, 3),
		Vector3(4, 5, 6),
		Vector3(7, 8, 9)
	);

	BOOST_ASSERT((m3(0, 1) == 2));
	BOOST_ASSERT((m3(1, 2) == 6));
	BOOST_ASSERT((m3(2, 0) == 7));

	std::cout << m1 << " * " << std::endl <<
		m2 << std::endl;
	std::cout << "should equal:" <<
		std::cout << Matrix3x3(
		Vector3(23, 14, 15),
		Vector3(39, 3, 7),
		Vector3(32, 10, 12)
		) << std::endl;


	BOOST_ASSERT((m1 * m2) == Matrix3x3(
		Vector3(23, 14, 15),
		Vector3(39, 3, 7),
		Vector3(32, 10, 12)
	));

	std::cout << "got: " << (m1 * m2) << std::endl;
}

void testMatrix4x4()
{
	Matrix4x4 m1(
		Vector4(2, 2, 1, 1),
		Vector4(1, 2, 3, 4),
		Vector4(5, 6, 7, 8),
		Vector4(2, 2, 2, 2)
	);

	Matrix4x4 m2(
		Vector4(2, 3, 2, 3),
		Vector4(5, 6, 7, 8),
		Vector4(2, 3, 2, 3),
		Vector4(5, 6, 7, 8)
	);

	BOOST_ASSERT((m1 * m2) == Matrix4x4(
		Vector4(23, 28, 31, 36),
		Vector4(67, 80, 88, 101),
		Vector4(23, 28, 31, 36),
		Vector4(67, 80, 88, 101)
	));

	std::cout << "Rotation" << std::endl;
	BOOST_ASSERT(Matrix4x4::rotationZ(Degrees(90)) * Vector3(1, 0, 0) == Vector3(0, 1, 0));

	Matrix4x4 m = Matrix4x4::identity();
	std::cout << "The matrix:" << std::endl;
	std::cout << m << std::endl;
	std::cout << "Rotated 90 degrees around x:" << std::endl;
	std::cout << (Matrix4x4::rotationX(Degrees(90))) << std::endl;
	std::cout << "Rotated 90 degrees around y:" << std::endl;
	std::cout << (Matrix4x4::rotationY(Degrees(90))) << std::endl;
	std::cout << "Rotated 90 degrees around z:" << std::endl;
	std::cout << (Matrix4x4::rotationZ(Degrees(90))) << std::endl;

	std::cout << "Translation" << std::endl;
	BOOST_ASSERT(Matrix4x4::translation(Vector3(5.0, 3.0, 1.0)) * Vector3(1, 2, 3) == Vector3(6, 5, 4));
	BOOST_ASSERT(Matrix4x4::translation(Vector3(1, 0, 2)) * Vector3(3, 1, 0) == Vector3(4, 1, 2));
}

int main()
{
	try
	{
		testVector3();
		testMatrix3x3();
		testMatrix4x4();
		testAngles();
	}
	catch(char const* c)
	{
		std::cout << c << std::endl;
	}
}

