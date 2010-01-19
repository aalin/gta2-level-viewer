#ifndef MATRIX3X3_HPP
#define MATRIX3X3_HPP

class Matrix3x3 {
	public:
		Matrix3x3();
		Matrix3x3(const Vector3&, const Vector3&, const Vector3&);
		bool operator==(const Matrix3x3&) const;
		Matrix3x3 operator*(const Matrix3x3&) const;
		Vector3 operator*(const Vector3&) const;
		friend std::ostream& operator<<(std::ostream&, const Matrix3x3&);

		float operator()(int col, int row) const
		{
			if(col < 0 || row < 0 || col > 2 || row > 2)
				throw "col and row should be 0..2";
			return _v[col][row];
		}
		float& operator()(int col, int row)
		{
			if(col < 0 || row < 0 || col > 2 || row > 2)
				throw "col and row should be 0..2";
			return _v[col][row];
		}

	private:
		float _v[3][3];
};

#endif

