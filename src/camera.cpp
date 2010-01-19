#include "common.hpp"

Camera::Camera()
{
	_position = Vector3(5.0,-30.0, 5.0);
	_forward = Vector3(0.0,1.0, 0.0);
	_right = Vector3(1.0, 0.0, 0.0);
	_up = Vector3(0.0, 0.0, 1.0);
}

void
Camera::update()
{ }

void
Camera::set(const Vector3& pos, const Vector3& forward, const Vector3& up)
{
	_position = pos;
	_forward = forward;
	_up = up;
}

void
Camera::rotateX(const Angle& angle)
{
	_forward = (
		_forward * angle.cos() +
		_up * angle.sin()
	).normalize();
	//_up = _forward.crossProduct(_right) * -1;
	_up = Vector3(0.0, 0.0, 1.0);
}

void
Camera::rotateY(const Angle& angle)
{
	_forward = (
		_forward * angle.cos() -
		_right * angle.sin()
	).normalize();
	_right = _forward.crossProduct(_up);
}

void
Camera::rotateZ(const Angle& angle)
{
	_right = (
		_right * angle.cos() +
		_up * angle.sin()
	).normalize();
	//_up = _forward.crossProduct(_right) * -1;
	_up = Vector3(0.0, 0.0, 1.0);
}

void
Camera::draw() const
{
	Vector3 point = _position + _forward;
	gluLookAt(
		_position.x, _position.y, _position.z,
		point.x, point.y, point.z,
		_up.x, _up.y, _up.z
	);
}

void
Camera::move(const Vector3& v)
{
	_position *= Matrix4x4::translation(v);
}

void
Camera::strafe(float distance)
{
	_position = _position + _right * distance;
}

void
Camera::moveForward(float distance)
{
	_position = _position + _forward * distance;
}

