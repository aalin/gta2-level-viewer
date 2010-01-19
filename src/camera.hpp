#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
	public:
		Camera();
		void set(const Vector3&, const Vector3&, const Vector3&);
		void move(const Vector3&);
		void moveForward(float);
		void strafe(float);
		void rotateX(const Angle&);
		void rotateY(const Angle&);
		void rotateZ(const Angle&);
		void getPosition() const;
		void update();
		void draw() const;
		void debug() const;
	private:
		Vector3 _up;
		Vector3 _forward;
		Vector3 _right;
		Vector3 _position;
};

#endif

