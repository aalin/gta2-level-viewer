#ifndef ANGLE_HPP
#define ANGLE_HPP

class Angle {
	public:
		Angle(float value);
		Angle();
		virtual ~Angle();

		float value() const { return _value; }
		virtual float getFullCircle() const = 0;

		float cos() const;
		float sin() const;
		float tan() const;

		Angle& setValue(float value) { _value = value; return *this; }
	protected:
		float _value;
		float convert(const Angle& angle) const;
};

class Radians : public Angle {
	public:
		Radians(float f) : Angle(f) {}
		Radians(const Angle&);
		float getFullCircle() const { return 2 * Math::PI; }
};

class Degrees : public Angle {
	public:
		Degrees(float f) : Angle(f) {}
		Degrees(const Angle&);
		float getFullCircle() const { return 360.0; }
};

inline float Angle::cos() const { return std::cos(Radians(*this).value()); }
inline float Angle::sin() const { return std::sin(Radians(*this).value()); }
inline float Angle::tan() const { return std::tan(Radians(*this).value()); }

#endif

