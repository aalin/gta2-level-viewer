#include "common.hpp"

Matrix4x4::Matrix4x4()
{
	for(int y = 0; y < 4; y++)
		for(int x = 0; x < 4; x++)
			_v[y][x] = 0.0;
}

Matrix4x4::Matrix4x4(const Matrix4x4& other)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			_v[i][j] = other(i, j);
}

Matrix4x4::Matrix4x4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
{
	_v[0][0] = a.x; _v[0][1] = a.y; _v[0][2] = a.z; _v[0][3] = a.w;
	_v[1][0] = b.x; _v[1][1] = b.y; _v[1][2] = b.z; _v[1][3] = b.w;
	_v[2][0] = c.x; _v[2][1] = c.y; _v[2][2] = c.z; _v[2][3] = c.w;
	_v[3][0] = d.x; _v[3][1] = d.y; _v[3][2] = d.z; _v[3][3] = d.w;
}

bool
Matrix4x4::operator==(const Matrix4x4& m) const
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			if(!(std::fabs(_v[i][j] - m(i, j)) < std::numeric_limits<float>::epsilon()))
				return false;
	return true;
}

Matrix4x4
Matrix4x4::operator*(const Matrix4x4& m) const
{
	Matrix4x4 ret;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			for(int k = 0; k < 4; k++)
				ret(j, i) += _v[k][i] * m(j, k);
	return ret;
}

Vector4
Matrix4x4::operator*(const Vector4& vec) const
{
	return Vector4(
		_v[0][0] * vec.x + _v[1][0] * vec.y + _v[2][0] * vec.z + _v[3][0] * vec.w,
		_v[0][1] * vec.x + _v[1][1] * vec.y + _v[2][1] * vec.z + _v[3][1] * vec.w,
		_v[0][2] * vec.x + _v[1][2] * vec.y + _v[2][2] * vec.z + _v[3][2] * vec.w,
		_v[0][3] * vec.x + _v[1][3] * vec.y + _v[2][3] * vec.z + _v[3][3] * vec.w
	);
}

Vector3
Matrix4x4::operator*(const Vector3& vec) const
{
	return Vector3(
		_v[0][0] * vec.x + _v[1][0] * vec.y + _v[2][0] * vec.z + _v[3][0],
		_v[0][1] * vec.x + _v[1][1] * vec.y + _v[2][1] * vec.z + _v[3][1],
		_v[0][2] * vec.x + _v[1][2] * vec.y + _v[2][2] * vec.z + _v[3][2]
	);
}

Vector2
Matrix4x4::operator*(const Vector2& vec) const
{
	return Vector2(
		_v[0][0] * vec.x + _v[1][0] * vec.y + _v[2][0],
		_v[0][1] * vec.x + _v[1][1] * vec.y + _v[2][1]
	);
}

Matrix4x4
Matrix4x4::transpose() const
{
	Matrix4x4 res;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			res(j, i) = _v[i][j];
	return res;
}

Matrix4x4
Matrix4x4::rotationX(const Angle& angle)
{
	return Matrix4x4(
		Vector4(1, 0, 0, 0),
		Vector4(0, angle.cos(), angle.sin(), 0),
		Vector4(0,-angle.sin(), angle.cos(), 0),
		Vector4(0, 0, 0, 1)
	);
}

Matrix4x4
Matrix4x4::rotationY(const Angle& angle)
{
	return Matrix4x4(
		Vector4(angle.cos(), 0,-angle.sin(), 0),
		Vector4(0, 1, 0, 0),
		Vector4(angle.sin(), 0, angle.cos(), 0),
		Vector4(0, 0, 0, 1)
	);
}

Matrix4x4
Matrix4x4::rotationZ(const Angle& angle)
{
	return Matrix4x4(
		Vector4( angle.cos(), angle.sin(), 0, 0),
		Vector4(-angle.sin(), angle.cos(), 0, 0),
		Vector4( 0, 0, 1, 0),
		Vector4( 0, 0, 0, 1)
	);
}

Matrix4x4
Matrix4x4::translation(const Vector3& v)
{
	return Matrix4x4(
		Vector4(1, 0, 0, 0),
		Vector4(0, 1, 0, 0),
		Vector4(0, 0, 1, 0),
		Vector4(v.x, v.y, v.z, 1)
	);
}

Matrix4x4
Matrix4x4::scale(const Vector3& v)
{
	return Matrix4x4(
		Vector4(v.x, 0, 0, 0),
		Vector4(0, v.y, 0, 0),
		Vector4(0, 0, v.z, 0),
		Vector4(0, 0, 0, 1)
	);
}

Matrix4x4&
Matrix4x4::setIdentity()
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			_v[i][j] = (i == j) ? 1 : 0;
	return *this;
}

Matrix4x4
Matrix4x4::identity()
{
	return Matrix4x4().setIdentity();
}

std::ostream&
operator<<(std::ostream& os, const Matrix4x4& m)
{
	os << "[ " << m(0,0) << "\t" << m(0,1) << "\t" << m(0,2) << "\t" << m(0,3) << std::endl <<
	      "  " << m(1,0) << "\t" << m(1,1) << "\t" << m(1,2) << "\t" << m(1,3) << std::endl <<
	      "  " << m(2,0) << "\t" << m(2,1) << "\t" << m(2,2) << "\t" << m(2,3) << std::endl <<
	      "  " << m(3,0) << "\t" << m(3,1) << "\t" << m(3,2) << "\t" << m(3,3) << " ]";
	return os;
}

