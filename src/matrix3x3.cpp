#include "common.hpp"

Matrix3x3::Matrix3x3()
{
	for(int y = 0; y < 3; y++)
		for(int x = 0; x < 3; x++)
			_v[y][x] = 0.0;
}

Matrix3x3::Matrix3x3(const Vector3& a, const Vector3& b, const Vector3& c)
{
	_v[0][0] = a.x; _v[0][1] = a.y; _v[0][2] = a.z;
	_v[1][0] = b.x; _v[1][1] = b.y; _v[1][2] = b.z;
	_v[2][0] = c.x; _v[2][1] = c.y; _v[2][2] = c.z;
}

bool
Matrix3x3::operator==(const Matrix3x3& m) const
{
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(!(std::fabs(_v[i][j] - m(i, j)) < std::numeric_limits<float>::epsilon()))
				return false;
	return true;
}

Matrix3x3
Matrix3x3::operator*(const Matrix3x3& m) const
{
	Matrix3x3 ret;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 3; k++)
				ret(j, i) += _v[k][i] * m(j, k);
	return ret;
}

Vector3
Matrix3x3::operator*(const Vector3& vec) const
{
	return Vector3(
		_v[0][0] * vec.x + _v[1][0] * vec.x + _v[2][0] * vec.x,
		_v[0][1] * vec.y + _v[1][1] * vec.y + _v[2][1] * vec.y,
		_v[0][2] * vec.z + _v[1][2] * vec.z + _v[2][2] * vec.z
	);
}

std::ostream&
operator<<(std::ostream& os, const Matrix3x3& m)
{
	os << "[ " << m(0,0) << "\t" << m(0,1) << "\t" << m(0,2) << std::endl <<
	      "  " << m(1,0) << "\t" << m(1,1) << "\t" << m(1,2) << std::endl <<
	      "  " << m(2,0) << "\t" << m(2,1) << "\t" << m(2,2) << " ]";
	return os;
}

