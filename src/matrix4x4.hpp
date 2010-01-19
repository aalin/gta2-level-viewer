#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

class Matrix4x4 {
	public:
		Matrix4x4();
		Matrix4x4(const Matrix4x4&);
		Matrix4x4(const Vector4&, const Vector4&, const Vector4&, const Vector4&);
		Matrix4x4(float, float, float, float,
		          float, float, float, float,
		          float, float, float, float,
		          float, float, float, float);
		bool operator==(const Matrix4x4&) const;
		Matrix4x4 operator*(const Matrix4x4&) const;
		Vector4 operator*(const Vector4&) const;
		Vector3 operator*(const Vector3&) const;
		Vector2 operator*(const Vector2&) const;
		Matrix4x4 transpose() const;

		friend std::ostream& operator<<(std::ostream&, const Matrix4x4&);

		Matrix4x4& setIdentity();

		static Matrix4x4 identity();
		static Matrix4x4 rotationX(const Angle&);
		static Matrix4x4 rotationY(const Angle&);
		static Matrix4x4 rotationZ(const Angle&);
		static Matrix4x4 translation(const Vector3&);
		static Matrix4x4 scale(const Vector3&);

		float operator()(int col, int row) const
		{
			if(col < 0 || row < 0 || col > 3 || row > 3)
				throw "col and row should be 0..3";
			return _v[col][row];
		}
		float& operator()(int col, int row)
		{
			if(col < 0 || row < 0 || col > 3 || row > 3)
				throw "col and row should be 0..3";
			return _v[col][row];
		}

	private:
		float _v[4][4];
};

#endif

