#pragma once
namespace Shabby {
	class V2 {
		double x_;
		double y_;
	public:
		static double Magnitude(const V2& u);
		static double SqrMagnitude(const V2& u);
		static V2 Normalized(const V2& u);
		static double Dot(const V2& u, const V2& v);

		V2 operator+(const V2& v) const;
		V2 operator-(const V2& v) const;
		V2 operator-() const;
		V2 operator*(double scalar) const;
		V2 operator/(double scalar) const;

		double GetX () const;
		void SetX(double x);
		double GetY() const;
		void SetY(double y);

		V2();
		V2(double x, double y);
		~V2();
	};
}

